import NativeModules from "react-native";
const NativeRCTKakaoSDK = NativeModules.NativeModules.KakaoSDK;

// Defined in https://developers.kakao.com/docs/ios-reference/KOSession_h/index.html#//apple_ref/c/tdef/NS_ENUM_DONTLINK_0
const KOAuthTypeTalk = 1 << 1;
const KOAuthTypeStory = 1 << 2;
const KOAuthTypeAccount = 1 << 3;

/**
 * @providesModule RCTKakaoSDK
 * @flow
 */
var RCTKakaoSDK = {
  KOAuthTypeTalk: KOAuthTypeTalk,
  KOAuthTypeStory: KOAuthTypeStory,
  KOAuthTypeAccount: KOAuthTypeAccount,
  sessionClose: function() {
    return NativeRCTKakaoSDK.sessionClose();
  },
  sessionOpen: function(authTypes) {
    if (!authTypes || authTypes.length === 0) {
      authTypes = [KOAuthTypeTalk, KOAuthTypeStory, KOAuthTypeAccount];
    }
    return NativeRCTKakaoSDK.sessionOpen(authTypes);
  },
  test: function() {
    NativeRCTKakaoSDK.test();
  }
};

module.exports = RCTKakaoSDK;
