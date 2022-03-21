#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define kHSSSDManagerDefaultDelegateSalt @"DEADBEEF"


@interface NSData(Encryption)

- (NSData *)encryptedDataWithSalt:(NSString*) salt;

/**
 Decrypts encrypted data.

 @discussion to resolve padding issues it should be in form DATA_LENGTH\0DATA
 */
- (nullable NSData *)decryptedDataWithSalt:(NSString*) salt;

- (NSData *)hashWithKey:(NSData *)keyData rounds:(NSUInteger)rounds;

@end

static const NSString *encryptedNSDataBareKeyKey = @"BareKey";
static const NSString *encryptedNSDataEncryptedKeyKey = @"EncryptedKey";
static const NSString *encryptedNSDataEncryptedDataKey = @"EncryptedData";


NS_ASSUME_NONNULL_END
