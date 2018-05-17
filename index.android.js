import NativeModules from "react-native";
const NativeRCTKakaoSDK = NativeModules.NativeModules.KakaoSDK;

// Defined in android kakao open sdk source (AuthType.java)
const KOAuthTypeTalk = 0;
const KOAuthTypeStory = 1;
const KOAuthTypeAccount = 2;

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
