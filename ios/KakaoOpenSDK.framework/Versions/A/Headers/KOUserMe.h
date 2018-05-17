/**
 * Copyright 2018 Kakao Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*!
 * @header KOUserMe.h
 * @abstract 사용자 정보 요청(user/me) API로 얻어오는 사용자 정보 관련 클래스
 */

#import <Foundation/Foundation.h>
#import "KOTalkMessageSending.h"
#import "KOSession.h"

NS_ASSUME_NONNULL_BEGIN

@class KOUserMeAccount;

/*!
 * @class KOUserMe
 * @abstract 사용자 정보를 나타내는 최상위 클래스. ID, 카카오계정 정보, 프로퍼티 등으로 구성됩니다.
 */
@interface KOUserMe : NSObject <NSCopying, KOTalkMessageSending>

/*!
 * @property hasSignedUp
 * @abstract 현재 로그인한 사용자가 앱에 연결(signup)되어 있는지 여부
 * @discussion 사용자관리 설정에서 자동연결 옵션을 off한 앱에서만 사용되는 값입니다. 자동연결의 기본값은 on이며 이 경우 값이 null로 반환되고 이미 연결되어 있음을 의미합니다.
 */
@property (readonly) KOOptionalBoolean hasSignedUp;
/*!
 * @property ID
 * @abstract 사용자의 고유 아이디
 * @discussion 사용자 ID는 앱 연결(signup)을 기준으로 발급됩니다.<br>
 *             1. 최초 로그인했을 때 발급<br>
 *             2. 자동연결을 off한 상태로 signup 호출에 성공했을 때 발급<br>
 *             3. 연결해제(unlink) 이후 1,2번 작업을 다시 수행하면 다른 값으로 재발급
 */
@property (readonly, nullable) NSString *ID;
/*!
 * @property account
 * @abstract 로그인한 카카오계정 정보. 이메일 등
 * @seealso KOUserMeAccount
 */
@property (readonly, nullable) KOUserMeAccount *account;
/*!
 * @property properties
 * @abstract 앱 별로 제공되는 사용자 정보 데이터베이스
 * @discussion 사용자에 대해 추가 정보를 저장할 수 있도록 데이터베이스를 제공합니다.<br>
 *             개발자사이트의 사용자 관리 > 앱 연동 설정 상태에 따라 카카오톡 또는 카카오스토리에 있는 닉네임과 프로필 이미지 정보를 앱 연결 시점에 복사하여 초기값으로 제공합니다.<br>
 *             1. nickname : 카카오톡 또는 카카오스토리에 설정된 닉네임<br>
 *             2. profile_image : 프로필 이미지 URL 문자열<br>
 *             3. thumbnail_image : 썸네일 사이즈의 프로필 이미지 URL 문자열
 */
@property (readonly, nullable) NSDictionary<NSString *, NSString *> *properties;
/*!
 * @property forPartner
 * @abstract 제휴를 통해 권한이 부여된 특정 앱에서 사용
 */
@property (readonly, nullable) NSDictionary<NSString *, id> *forPartner;

- (nonnull NSDictionary<NSString *, id> *)dictionary;
+ (instancetype)meWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end



/*!
 * @class KOUserMeAccount
 * @abstract 카카오계정 정보를 나타내는 클래스
 * @discussion 사용자의 동의를 받지 않은 개인정보는 값이 반환되지 않을 수 있습니다.
 *             동의를 받지 않아도 값의 존재여부는 has- 프로퍼티로 확인할 수 있습니다.<br>
 *             값이 내려오지 않은 정보의 has- 프로퍼티가 true인 경우 사용자 동의가 필요한 상황임을 의미하며 KOSession의 updateScopes 메소드를 이용하여 동의를 받을 수 있습니다. 동의를 받은 후 user/me를 다시 호출하면 해당 값이 반환될 것입니다.<br>
 *             has- 프로퍼티가 false라면 현재 로그인한 계정에 해당 정보가 등록되지 않은 상태이며 사용자의 동의도 요청할 수 없습니다.
 */
@interface KOUserMeAccount : NSObject <NSCopying>

/*!
 * @property email
 * @abstract 카카오계정에 등록한 이메일 정보
 * @discussion 7.2.0 이상 카카오톡을 설치하고 전화번호 인증을 완료하면 이메일이 없는 카카오계정이 생성됩니다. 해당 카카오계정으로 간편로그인이나 전화번호 로그인을 할 경우 이메일 값이 nil로 반환됩니다.<br>
 *             이메일이 있는 카카오계정이라도 사용자로부터 이메일 제공에 대한 동의를 받지 않으면 값이 nil로 반환됩니다. 등록된 이메일이 존재하지만 동의를 받지 않은 경우 hasEmail값이 true이고 사용자에게 이메일 제공에 대한 동의를 요청할 수 있습니다.
 * @seealso hasEmail
 * @seealso isEmailVerified
 */
@property (readonly, nullable) NSString *email;
/*!
 * @property isEmailVerified
 * @abstract 카카오계정에 이메일 등록 시 이메일 인증을 받았는지 여부
 * @seealso email
 */
@property (readonly) KOOptionalBoolean isEmailVerified;
/*!
 * @property hasEmail
 * @abstract 이메일 보유 여부
 * @discussion email이 nil이고 hasEmail이 true이면 KOSession의 updateScopes 메소드를 이용하여 사용자로부터 이메일 제공에 대한 동의를 받을 수 있습니다.<br>
 *             이메일 제공동의 scope ID는 "account_email"입니다.
 * @seealso email
 */
@property (readonly) KOOptionalBoolean hasEmail;



/*!
 * @property isKakaoTalkUser
 * @abstract 카카오톡 서비스 가입 여부
 * @discussion 제휴를 통해 권한이 부여된 특정 앱에서만 획득할 수 있습니다. 제휴되어 있지 않은 경우 nil이 반환됩니다.<br>
 *             카카오톡 카카오계정 설정에 연결되어 있는 카카오계정은 true가 반환됩니다.<br>
 *             사용자에게 동의를 받지 않았을 경우 null이 반환되며 KOSession의 updateScopes 메소드를 이용하여 사용자로부터 카카오톡 가입 여부에 대한 동의를 받을 수 있습니다.<br>
 *             카카오톡 서비스 가입 여부 scope ID는 "is_kakaotalk_user"입니다.
 */
@property (readonly) KOOptionalBoolean isKakaoTalkUser;



/*!
 * @property phoneNumber
 * @abstract 카카오톡에서 인증한 전화번호
 * @discussion 제휴를 통해 권한이 부여된 특정 앱에서만 획득할 수 있습니다.<br>
 *             카카오톡에 연결되어 있지 않은 카카오계정은 전화번호가 존재하지 않습니다.
 * @seealso hasPhoneNumber
 */
@property (readonly, nullable) NSString *phoneNumber;
/*!
 * @property hasPhoneNumber
 * @abstract 전화번호 보유 여부
 * @discussion 제휴를 통해 권한이 부여된 특정 앱에서만 획득할 수 있습니다. 제휴되어 있지 않은 경우 nil이 반환됩니다.<br>
 *             phoneNumber가 nil이고 hasPhoneNumber가 true이면 KOSession의 updateScopes 메소드를 이용하여 사용자로부터 전화번호 제공에 대한 동의를 받을 수 있습니다.<br>
 *             전화번호 제공동의 scope ID는 "phone_number"입니다.
 * @seealso phoneNumber
 */
@property (readonly) KOOptionalBoolean hasPhoneNumber;



/*!
 * @property displayID
 * @abstract 디스플레이용으로 제공되는 마스킹 처리된 email 또는 phoneNumber
 * @discussion 제휴를 통해 권한이 부여된 특정 앱에서만 획득할 수 있습니다.
 * @seealso email
 * @seealso phoneNumber
 */
@property (readonly, nullable) NSString *displayID;



- (nonnull NSDictionary<NSString *, id> *)dictionary;
+ (instancetype)accountWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END
