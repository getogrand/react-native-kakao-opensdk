#import <KakaoOpenSDK/KakaoOpenSDK.h>
#import <React/RCTConvert.h>
#import "RCTKakaoSDK.h"


@implementation RCTKakaoSDK

RCT_EXPORT_MODULE()

RCT_REMAP_METHOD(sessionClose,
                 resolver: (RCTPromiseResolveBlock)resolve
                 rejecter: (RCTPromiseRejectBlock)reject)
{
  [[KOSession sharedSession] close];
  resolve(nil);
}

RCT_REMAP_METHOD(sessionOpen,
                 sessionOpenWithAuthTypes: (NSArray<NSNumber *> *) authTypes
                 resolver: (RCTPromiseResolveBlock)resolve
                 rejecter: (RCTPromiseRejectBlock)reject)
{
  KOSession *session = [KOSession sharedSession];

  KOSessionCompletionHandler handler = ^(NSError *error) {
    if (error) {
      if ([error code] == KOErrorCancelled) {
        resolve(nil);
        return;
      }

      reject([error localizedDescription], [error localizedFailureReason], error);
      return;
    }

    [self resolveUserInfo: resolve rejectIfError: reject ];
  };

  if (authTypes == nil || [authTypes count] == 0) {
    [session openWithCompletionHandler: handler];
    return;
  }

  [session openWithCompletionHandler: handler authTypes:authTypes];
}

- (void)resolveUserInfo: (RCTPromiseResolveBlock)resolve
          rejectIfError: (RCTPromiseRejectBlock)reject
{
  [KOSessionTask userMeTaskWithCompletion:^(NSError *error, KOUserMe *me) {
    if (error) {
      reject([error localizedDescription], [error localizedFailureReason], error);
      return;
    }

    KOSession *session = [KOSession sharedSession];
    NSDictionary<NSString *, NSString *> *properties = [me properties];
    KOUserMeAccount *account = [me account];

    NSString *nickname = properties[@"nickname"];
    NSString *profileImage = properties[@"profile_image"];
    NSString *thumbnailImage = properties[@"thumbnail_image"];
    NSString *email = [account email];
    NSString *phoneNumber = [account phoneNumber];

    resolve(@{
              @"id": [me ID],
              @"nickname": nickname ? nickname : @"",
              @"profileImage": profileImage ? profileImage : @"",
              @"thumbnailImage": thumbnailImage ? thumbnailImage : @"",
              @"email": email ? email : @"",
              @"phoneNumber": phoneNumber ? phoneNumber : @"",
              @"accessToken": [[session token] accessToken]
              });
  }];
}

- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

- (NSDictionary *)constantsToExport
{
  return @{
           @"KOAuthTypeTalk": @(KOAuthTypeTalk),
           @"KOAuthTypeStory": @(KOAuthTypeStory),
           @"KOAuthTypeAccount": @(KOAuthTypeAccount)
           };
}

@end
