//===-- EVAuthenticator.h - EVAuthenticator class definition --------===//
//
// EyeVerify Codebase
//
//===----------------------------------------------------------------------===//
///
/// @file
/// @brief This file contains the declaration of the EVAuthenticator class.
///
//===----------------------------------------------------------------------===//

#import "EVAuthenticatorDelegate.h"

#import "EyeVerify.h"
#import "VideoCamera.h"
#import "EyeVerifyRemote.h"

@protocol EyeVerifyDelegate2;
@protocol EyeVerifyDelegate;

@interface EVAuthenticator : NSObject <EVAuthenticatorDelegate>

@property (nonatomic, readonly) BOOL isBusy;
@property (nonatomic, copy) NSString *userName;
@property (nonatomic, strong) NSData *userKey;
@property (nonatomic, weak) UIView *captureView;

@property (nonatomic, weak) id<EVAuthSessionDelegate> authSessionDelegate;

- (instancetype)initWithLicense:(NSString *)license_certificate delegate:(id)delegate;

- (license_result_enum)validateLicense:(NSString *)license;
- (BOOL)isUserEnrolled:(NSString *)user;
- (NSArray*)getEnrolledUsers;
- (void)deleteEnrollments;

- (void)cancelRequest:(abort_reason_enum)reason;
- (void)captureEnrollment:(BOOL)continueAuth;
- (void)captureVerification;
- (void)continueAuth;

- (void)processRemoteMessage:(eyeverify_message_type)message_type data:(NSData *)nsdata;
- (void)importSettings:(NSData*)settings;

- (void) pause;
- (void) resume;

+ (EVAuthenticator *) getInstance;
- (void) dispatch_evp:(dispatch_block_t)block;
- (void) dispatch_evp_get_result:(dispatch_block_t)block;

@end

@protocol EyeVerifyDelegate2 <NSObject>

- (void)authenticator:(EVAuthenticator *)authenticator enrollmentCompleted:(enroll_result_enum)result abortReason:(abort_reason_enum)abort_reason;
- (void)authenticator:(EVAuthenticator *)authenticator verificationCompleted:(verify_result_enum)result userKey:(NSData *)userKey abortReason:(abort_reason_enum)abort_reason;

@end


@protocol EyeVerifyDelegate <NSObject>

- (void)enrollmentCompleted:(BOOL)enrolled error:(NSError *)error DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.8.3.");
- (void)verificationCompleted:(BOOL)verified userKey:(NSData *)userKey error:(NSError *)error DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.8.3.");

@end


@interface EVAuthenticator (EVAuthenticatorDeprecated)

- (instancetype)initWithLicense:(NSString *)license_certificate delegate:(id<EyeVerifyDelegate>)delegate DEPRECATED_MSG_ATTRIBUTE("Deprecated in v2.8.3.");

@end
