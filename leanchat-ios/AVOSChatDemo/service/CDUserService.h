//
//  UserService.h
//  AVOSChatDemo
//
//  Created by lzw on 14-10-22.
//  Copyright (c) 2014年 AVOS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CDCommon.h"
#import "CDAddRequest.h"
#import "CDAbuseReport.h"

@interface CDUserService : NSObject

+(void)findFriendsWithBlock:(AVArrayResultBlock)block;

+(void)isMyFriend:(AVUser*)user block:(AVBooleanResultBlock)block;

+(void)findUsersByPartname:(NSString*)partName withBlock:(AVArrayResultBlock)block;

+(NSString*)getPeerIdOfUser:(AVUser*)user;

+(void)findUsersByIds:(NSArray*)userIds callback:(AVArrayResultBlock)callback;

+(void)displayAvatarOfUser:(AVUser*)user avatarView:(UIImageView*)avatarView;

+(UIImage*)getAvatarOfUser:(AVUser*)user;

+(void)saveAvatar:(UIImage*)image callback:(AVBooleanResultBlock)callback;

+(void)addFriend:(AVUser*)user callback:(AVBooleanResultBlock)callback;

+(void)removeFriend:(AVUser*)user callback:(AVBooleanResultBlock)callback;

+(void)countAddRequestsWithBlock:(AVIntegerResultBlock)block;

+(void)findAddRequestsWithBlock:(AVArrayResultBlock)block;

+(void)agreeAddRequest:(CDAddRequest*)addRequest callback:(AVBooleanResultBlock)callback;

+(void)tryCreateAddRequestWithToUser:(AVUser*)user callback:(AVBooleanResultBlock)callback;

+(void)reportAbuseWithReason:(NSString*)reason convid:(NSString*)convid block:(AVBooleanResultBlock)block;

@end
