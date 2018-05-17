//
//  RCTConvert+KOAuthType.m
//  RCTKakaoSDK
//
//  Created by WonyoungJu on 2018. 5. 15..
//  Copyright © 2018년 Facebook. All rights reserved.
//

#import "RCTConvert+KOAuthType.h"
#import <KakaoOpenSDK/KakaoOpenSDK.h>

@implementation RCTConvert (KOAuthType)
RCT_ENUM_CONVERTER(KOAuthType,
                   (@{
                      @"KOAuthTypeTalk": @(KOAuthTypeTalk),
                      @"KOAuthTypeStory": @(KOAuthTypeStory),
                      @"KOAuthTypeAccount": @(KOAuthTypeAccount)
                      }),
                   KOAuthTypeTalk,
                   integerValue)
@end
