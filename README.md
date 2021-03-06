![leanchat1](https://cloud.githubusercontent.com/assets/5022872/7332357/41c39c82-eb6e-11e4-8224-9c6908c9fa75.gif)

## 介绍
这个示例项目是为了帮助使用 LeanCloud 的开发者快速实现具有实时通讯功能的应用。

#### 注意：若要集成，我们推荐封装性更好的 [MessageDisplayKit](https://github.com/xhzengAIB/MessageDisplayKit/tree/master/Example/MessageDisplayKitLeanchatExample)

## 子项目介绍
* LeanChatLib ，核心的聊天逻辑和聊天界面库。有了它，可以快速集成聊天功能，支持文字、音频、图片、表情消息，消息通知。同时也有相应的 [Android 版本](https://github.com/leancloud/leanchat-android)。
* LeanChatExample，leanchatlib 最简单的使用例子。展示了如何用少量代码调用 LeanChatLib 来加入聊天，无论是用 LeanCloud 的用户系统还是自己的用户系统。
* LeanChat-ios，为 LeanChat 整个应用。它包含好友管理、群组管理、地理消息、附近的人、个人页面、登录注册的功能，完全基于 LeanCloud 的存储和通信功能。它也是对 LeanChatLib 更复杂的应用。

## 分支
* master 分支，使用了 LeanCloud 的实时通信服务2.0 （推荐）
* v1 分支，使用了 LeanCloud 的实时通信服务 1.0

## 运行
* 打开 `LeanChat.xcworkspace`

## 如何三步加入IM
1. LeanCloud 中创建应用       
2. 创建项目，加入 LeanChatLib 作为Library。拷贝Resources文件夹，
3. 依次在合适的地方加入以下代码，

应用启动后，初始化，以及配置 IM User
```objc
   [AVOSCloud setApplicationId: YourAppID clientKey: YourAppKey];
   [CDIMConfig config].userDelegate=[[CDUserFactory alloc] init];   
```

配置一个 UserFactory，遵守 CDUserDelegate协议即可。

```objc
#import "CDUserFactory.h"

#import <LeanChatLib/LeanChatLib.h>

@interface CDUserFactory ()<CDUserDelegate>

@end


@implementation CDUserFactory

#pragma mark - CDUserDelegate
-(void)cacheUserByIds:(NSSet *)userIds block:(AVIMArrayResultBlock)block{
    block(nil,nil); // don't forget it
}

-(id<CDUserModel>)getUserById:(NSString *)userId{
    CDUser* user=[[CDUser alloc] init];
    user.userId=userId;
    user.username=userId;
    user.avatarUrl=@"http://ac-x3o016bx.clouddn.com/86O7RAPx2BtTW5zgZTPGNwH9RZD5vNDtPm1YbIcu";
    return user;
}

@end

```

这里的 CDUser 是应用内的User对象，你可以在你的User对象实现 CDUserModel 协议即可。

CDUserModel，
```objc
@protocol CDUserModel <NSObject>

@required

-(NSString*)userId;

-(NSString*)avatarUrl;

-(NSString*)username;

@end
```

登录时调用，
```objc
        CDIM* im=[CDIM sharedInstance];
        [im openWithClientId:selfId callback:^(BOOL succeeded, NSError *error) {
            if(error){
                DLog(@"%@",error);
            }else{
                [self performSegueWithIdentifier:@"goMain" sender:sender];
            }
        }];
```

和某人聊天，
```objc
        [[CDIM sharedInstance] fetchConvWithOtherId:otherId callback:^(AVIMConversation *conversation, NSError *error) {
            if(error){
                DLog(@"%@",error);
            }else{
                LCEChatRoomVC* chatRoomVC=[[LCEChatRoomVC alloc] initWithConv:conversation];
                [weakSelf.navigationController pushViewController:chatRoomVC animated:YES];
            }
        }];
```

和多人群聊，
```objc
        CDIM* im=[CDIM sharedInstance];
        NSMutableArray* memberIds=[NSMutableArray array];
        [memberIds addObject:groupId1];
        [memberIds addObject:groupId2];
        [memberIds addObject:im.selfId];
        [im fetchConvWithMembers:memberIds callback:^(AVIMConversation *conversation, NSError *error) {
            if(error){
                DLog(@"%@",error);
            }else{
                LCEChatRoomVC* chatRoomVC=[[LCEChatRoomVC alloc] initWithConv:conversation];
                [weakSelf.navigationController pushViewController:chatRoomVC animated:YES];
            }
        }];
```

注销时，
```objc
    [[CDIM sharedInstance] closeWithCallback:^(BOOL succeeded, NSError *error) {
        DLog(@"%@",error);
    }];
```

然后，就可以像上面截图那样聊天了。


## 使用 LeanChatLib 需知

1. 如何引入LeanChatLib 依赖
首先，打开LeanChatLib文件夹，拖动到你的项目中，如图，

![qq20150407-1](https://cloud.githubusercontent.com/assets/5022872/7016274/b1b03672-dd13-11e4-8ddd-4c501c59dbf0.png)

复制资源文件，

![qq20150414-2](https://cloud.githubusercontent.com/assets/5022872/7122215/816ffc2a-e24c-11e4-997f-9cb7a547ac99.png)


之后，项目依赖图，如，

![qq20150407-2](https://cloud.githubusercontent.com/assets/5022872/7016279/d214abe6-dd13-11e4-8c16-900593bdb33e.png)
![3](https://cloud.githubusercontent.com/assets/6140508/7111296/981733a0-e1f0-11e4-9ff4-06f3f2c54817.png)


之后可以进行第二点。        
2. 必须允许 LeanChatLib中的项目直接include framework里的头文件，设置选项为 YES，如图，
![qq20150403-1](https://cloud.githubusercontent.com/assets/5022872/6982020/5d34db2a-da3e-11e4-8ef2-2521255bb923.png) 
3. 加 Linker Flags ，
![qq20150410-2 2x](https://cloud.githubusercontent.com/assets/5022872/7089833/29ebf332-dfd1-11e4-9953-a3c7285daf76.png)

4. 需要若干 Framework的支持，参考 LeanChatExample


## 部署 LeanChat 需知

如果要部署完整的LeanChat的话，因为该应用有添加好友的功能，请在设置->应用选项中，勾选互相关注选项，以便一方同意的时候，能互相加好友。

![qq20150407-5](https://cloud.githubusercontent.com/assets/5022872/7016645/53f91bb8-dd1b-11e4-8ce0-72312c655094.png)

## 开发指南

[实时通信服务开发指南](https://leancloud.cn/docs/realtime_v2.html)

[Wiki](https://github.com/leancloud/leanchat-android/wiki)

## [更多介绍](https://github.com/leancloud/leanchat-android)

## 致谢

感谢曾宪华大神的 [MessageDisplayKit](https://github.com/xhzengAIB/MessageDisplayKit) 开源库。
