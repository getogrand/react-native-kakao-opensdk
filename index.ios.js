/**
 * @providesModule RCTKakaoSDK
 * @flow
 */
var NativeRCTKakaoSDK = require('react-native/NativeModules').KakaoSDK

/**
 * High-level docs for the RCTKakaoSDK iOS API can be written here.
 */

var RCTKakaoSDK = {
  KOAuthTypeTalk: NativeRCTKakaoSDK.KOAuthTypeTalk,
  KOAuthTypeStory: NativeRCTKakaoSDK.KOAuthTypeStory,
  KOAuthTypeAccount: NativeRCTKakaoSDK.KOAuthTypeAccount,
  sessionClose: function() {
    return NativeRCTKakaoSDK.sessionClose()
  },
  sessionOpen: function(authTypes) {
    if (!authTypes || authTypes.length === 0) {
      authTypes = [
        NativeRCTKakaoSDK.KOAuthTypeTalk,
        NativeRCTKakaoSDK.KOAuthTypeStory,
        NativeRCTKakaoSDK.KOAuthTypeAccount,
      ]
    }
    return NativeRCTKakaoSDK.sessionOpen(authTypes)
  },
  test: function() {
    NativeRCTKakaoSDK.test()
  },
}

module.exports = RCTKakaoSDK
