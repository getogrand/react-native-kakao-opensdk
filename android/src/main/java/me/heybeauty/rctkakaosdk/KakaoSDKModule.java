package me.heybeauty.rctkakaosdk;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.WritableMap;
import com.kakao.auth.ApiResponseCallback;
import com.kakao.auth.AuthService;
import com.kakao.auth.AuthType;
import com.kakao.auth.ISessionCallback;
import com.kakao.auth.KakaoAdapter;
import com.kakao.auth.KakaoSDK;
import com.kakao.auth.Session;
import com.kakao.auth.authorization.accesstoken.AccessToken;
import com.kakao.auth.network.response.AccessTokenInfoResponse;
import com.kakao.network.ErrorResult;
import com.kakao.usermgmt.UserManagement;
import com.kakao.usermgmt.callback.MeResponseCallback;
import com.kakao.usermgmt.callback.MeV2ResponseCallback;
import com.kakao.usermgmt.response.MeV2Response;
import com.kakao.usermgmt.response.model.UserAccount;
import com.kakao.usermgmt.response.model.UserProfile;
import com.kakao.util.exception.KakaoException;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class KakaoSDKModule extends ReactContextBaseJavaModule {
  private static final String LOG_TAG = "KakaoSDKModule";

  private final KakaoSDKAdapter kakaoSDKAdapter;

  public KakaoSDKModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.kakaoSDKAdapter = new KakaoSDKAdapter(reactContext.getCurrentActivity());
    try {
      KakaoSDK.init(this.kakaoSDKAdapter);
    } catch (KakaoSDK.AlreadyInitializedException e) {
      // do nothing
    } // other exceptions will be thrown
  }

  @Override
  public String getName() {
    return "KakaoSDK";
  }

  @Override
  public Map<String, Object> getConstants() {
    final Map<String, Object> constants = new HashMap<>();
    constants.put("KOAuthTypeTalk", AuthType.KAKAO_TALK);
    constants.put("KOAuthTypeStory", AuthType.KAKAO_STORY);
    constants.put("KOAuthTypeAccount", AuthType.KAKAO_ACCOUNT);
    return constants;
  }

  @ReactMethod
  public void closeSession(Promise promise) {
    Session session = Session.getCurrentSession();
    if (!session.isOpened()) {
      promise.resolve(true);
      return;
    }

    session.close();
    promise.resolve(true);
  }

  @ReactMethod
  public void openSession(ReadableArray authTypes, Promise promise) {
    List<Object> authTypeList = authTypes.toArrayList();

    AuthType authType;
    if (authTypeList.size() == 1) {
      authType = (AuthType) authTypeList.get(0);
    } else {
      authType = AuthType.KAKAO_LOGIN_ALL;
    }

    Session session = Session.getCurrentSession();
    session.open(authType, getReactApplicationContext().getCurrentActivity());
  }

  private class SessionCallback implements ISessionCallback {
    Promise promise;

    public SessionCallback(Promise promise) {
      this.promise = promise;
    }

    @Override
    public void onSessionOpened() {
      Session session = Session.getCurrentSession();
      final AccessToken tokenInfo = session.getTokenInfo();

      MeV2ResponseCallback meV2ResponseCallback = new MeV2ResponseCallback() {
        @Override
        public void onSessionClosed(ErrorResult errorResult) {
          promise.reject(errorResult.toString(), errorResult.getException());
        }

        @Override
        public void onSuccess(MeV2Response meV2Response) {
          long id = meV2Response.getId();
          String nickname = meV2Response.getNickname();
          String profileImage = meV2Response.getProfileImagePath();
          String thumbnailImage = meV2Response.getThumbnailImagePath();
          UserAccount kakaoAccount = meV2Response.getKakaoAccount();
          String email = kakaoAccount.getEmail();
          String phoneNumber = kakaoAccount.getPhoneNumber();
          String accessToken = tokenInfo.getAccessToken();

          WritableMap map = Arguments.createMap();
          map.putString("id", String.valueOf(id));
          map.putString("nickname", nickname);
          map.putString("profileImage", profileImage);
          map.putString("thumbnailImage", thumbnailImage);
          map.putString("email", email);
          map.putString("phoneNumber", phoneNumber);
          map.putString("accessToken", accessToken);
          promise.resolve(map);
        }
      };
      UserManagement.getInstance().me(meV2ResponseCallback);
    }

    @Override
    public void onSessionOpenFailed(KakaoException e) {
      if (e.isCancledOperation()) {
        this.promise.resolve(true);
        return;
      }

      this.promise.reject(e.getErrorType().name(), "kakao session open failed", e);
    }
  }
}
