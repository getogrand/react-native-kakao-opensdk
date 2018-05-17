package me.heybeauty.rctkakaosdk;

import android.app.Activity;
import android.content.Context;

import com.kakao.auth.ApprovalType;
import com.kakao.auth.AuthType;
import com.kakao.auth.IApplicationConfig;
import com.kakao.auth.ISessionConfig;
import com.kakao.auth.KakaoAdapter;

public class KakaoSDKAdapter extends KakaoAdapter {
  private static final AuthType[] defaultAuthTypes = new AuthType[]{
    AuthType.KAKAO_TALK,
    AuthType.KAKAO_STORY,
    AuthType.KAKAO_ACCOUNT
  };

  private final Activity activity;
  private AuthType[] authTypes;

  public KakaoSDKAdapter(Activity activity) {
    this(activity, defaultAuthTypes);
  }

  public KakaoSDKAdapter(Activity activity, AuthType[] authTypes) {
    this.activity = activity;
    this.authTypes = authTypes;
  }

  public AuthType[] getAuthTypes() {
    return this.authTypes;
  }

  public void setAuthTypes(AuthType[] authTypes) {
    this.authTypes = authTypes;
  }

  @Override
  public ISessionConfig getSessionConfig() {
    return new ISessionConfig() {
      @Override
      public AuthType[] getAuthTypes() {
        return authTypes;
      }

      @Override
      public boolean isUsingWebviewTimer() {
        return false;
      }

      @Override
      public boolean isSecureMode() {
        return false;
      }

      @Override
      public ApprovalType getApprovalType() {
        return ApprovalType.INDIVIDUAL;
      }

      @Override
      public boolean isSaveFormData() {
        return false;
      }
    };
  }

  @Override
  public IApplicationConfig getApplicationConfig() {
    return new IApplicationConfig() {
      @Override
      public Context getApplicationContext() {
        return activity.getApplicationContext();
      }
    };
  }
}
