# Before You Start

In order to be able to use the SDK, the following steps have to be done:

1. Register an account at [developer.anchorfree.com](https://developer.anchorfree.com)
2. Create a project and use a name for your project as a Public key. Private key is optional.
3. Use SDK with a `carrierId` equals to the given *Public Key* and `baseURLString` equals to *URL* from the project details.

# HydraKit

HydraKit is created to help developers to achieve anti-blocking features for mobie applications. This toolkit protects all qualifying HTTP/HTTPS requests across the application.

### Features

- Protects your API calls from being blocked by IP address or DNS name.
- Protects your API calls from being eavesdropped by third-party.
- Protects user data such as cookies, tokens and sessions across the application.

## Installation

### Framework (static)

Download [HydraKit.framework for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FHydraKit.framework.zip?alt=media&token=ed306210-7743-4d13-8689-38d55bcc32d6)

Add **HydraKit.framework** to your project.

In your project: *Project* > *Build Settings*:
- Set "Enable bitcode" to **NO**
- Set "Other Linker Flags" to `-ObjC`.

In your project: *Project* > *General*:
- Add `libz.tbd` to **Linked Frameworks and Libraries**.

## Getting Started

First, configure `HydraKit` with API backend `baseURLString` and `carrierId`:

    #import <HydraKit/HydraKit.h>

    // ...

    NSString *baseURLString = @"{Your Base URL String}";
    NSString *carrierId = @"{Your Carrier ID}";
    AFPHydraKitConfig *hydraKitConfig = [AFPHydraKitConfig hydraKitConfigWithBaseURLString:baseURLString carrierId:carrierId];

    [HydraKit appDidLaunch:hydraKitConfig];

The best place to initialize `HydraKit` with `AFPHydraKitConfig` is

    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions

method of your `AppDelegate` implementation.

HydraKit can work in two modes:

1. Protected `NSURLSession` on-demand.

2. Protect all qualifying `NSURLSession` instances and `NSURLConnection` instances across the application (this mode also protects all WebView requests).

### 1. `NSURLSession` on-demand

If your application is fully compatible with `NSURLSession` then it's a good option to protect your API calls by acquiring protected `NSURLSession` instance. Change your code to work with `NSURLSession` in async way:

    [HydraKit protectedURLSessionWithCompletion:^(NSURLSession *session) {
        [self sendRequest:request withSesssion:session];
    }];

Whenever anti-blocking services are ready, you'll get `session` instance that is protected.

### 2. Automatic protection

If your application uses mixed both `NSURLSession` and `NSURLConnection`, or you just want to do everything automagically – then call register protocol function:

    [HydraKit registerURLProtocol];

This function registers special URL protocol that protects your app API requests (both HTTP and HTTPS) and routes it to anti-blocking services. If you're don't need protection anymore, unregister protection protocol:

    [HydraKit unregisterURLProtocol];

> **NOTE:** Do not use `[HydraKit protectedURLSessionWithCompletion: /* ... */ ]` in this case.

## Example

Here is a simple example of protected **GET** request to some URL.

    @import HydraKit;

    // ...

    NSURL *URL = [NSURL URLWithString:@"http://ip-api.com/json"];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:URL];
    [request setHTTPMethod:@"GET"];

    [HydraKit protectedURLSessionWithCompletion:^(NSURLSession *session) {
      NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request
       completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
          NSString *responseData = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
      }];

      [dataTask resume];
    }];

After this code executes, `responseData` should have a page that shows different IP address.

## Status

HydraKit allows you to monitor its current status (`HydraKitStatus` enum) by subscribing to `HydraKitDidChangeStatusNotification` notification via an `NSNotificationCenter` instance.

    #import <HydraKit/HydraKit.h>

    // ...

    NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self
                           selector:@selector(hydraKitDidChangeStatus:)
                               name:HydraKitDidChangeStatusNotification
                             object:nil];

    // ...

    - (void)hydraKitDidChangeStatus:(NSNotification *)notification {
    
        switch (HydraKit.sharedKit.status) {
            case HydraKitStatusStatusStopped:
                NSLog(@"> Stopped");
                break;
    
            case HydraKitStatusStatusStarting:
                NSLog(@"> Starting");
                break;
    
            case HydraKitStatusStatusStarted:
                NSLog(@"> Started");
                break;
    
            case HydraKitStatusStatusStopping:
                NSLog(@"> Stopping");
                break;

            case HydraKitStatusStatusRecovering:
                NSLog(@"> Recovering");
                break;
        }
    }

## Handling Errors

Along with a status, HydraKit also might send an `NSError` error as a part of `NSNotification`'s `userInfo`. Subscribe for `HydraKitDidChangeStatusNotification` notification as described in **Status** section and process notification.

    if (notification.userInfo && notification.userInfo[@"lastError"]) {
        NSError *hydraError = notification.userInfo[@"lastError"];
        NSLog(@"hydraError: %@", hydraError.localizedDescription);
    }

Latest error the HydraKit has encountered is available through `HydraKit.sharedKit.lastError`.
