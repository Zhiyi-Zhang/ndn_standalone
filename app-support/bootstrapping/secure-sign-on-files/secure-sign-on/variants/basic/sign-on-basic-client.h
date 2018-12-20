/*
 * Copyright (C) Edward Lu
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 * See AUTHORS.md for complete list of NDN IOT PKG authors and contributors.
 */

#ifndef SIGN_ON_BASIC_CLIENT_H
#define SIGN_ON_BASIC_CLIENT_H

#include "sign-on-basic-client-consts.h"

#include "sign-on-basic-sec-intf-setter.h"

#include <stddef.h>
#include <stdint.h>

/**@brief Generic function interface for generating a sha256 hash. Returns SEC_OP_SUCCESS on success,
 *          SEC_OP_FAILURE on failure.
 *
 * @param[in]   payload                    Payload to be hashed.
 * @param[in]   payload_len                Length of payload to be hashed.
 * @param[in]   output                     Buffer where hash will be outputted. Hash will be of length 
 *                                           SIGN_ON_BASIC_SHA256_HASH_SIZE.
 *
 */
typedef int (*sign_on_basic_sec_gen_sha256_hash)(const uint8_t *payload, uint16_t payload_len, 
                                                     uint8_t *output);

/**@brief Generic function interface for generating the N1 keypair. Returns SEC_OP_SUCCESS on success,
 *          SEC_OP_FAILURE on failure.
 *
 * @param[in]   pub_key_buf                Pre-allocated buffer where generated public key will be stored.
 * @param[in]   pub_key_buf_len            Length of pub_key_buf.
 * @param[in]   pub_key_output_len         Variable where length of public key will be stored, if generation
 *                                           is successful.
 * @param[in]   pri_key_buf                Pre-allocated buffer where generated private key will be stored.
 * @param[in]   pri_key_buf_len            Length of pri_key_buf.
 * @param[in]   pri_key_output_len         Variable where length of private key will be stored, if generation
 *                                           is successful.
 *
 */
typedef int (*sign_on_basic_sec_gen_n1_keypair)(uint8_t *pub_key_buf, uint16_t pub_key_buf_len, 
                                                 uint16_t *pub_key_output_len,
                                                 uint8_t *pri_key_buf, uint16_t pri_key_buf_len, 
                                                 uint16_t *pri_key_output_len);


/**@brief Generic function interface for generating KT. Returns SEC_OP_SUCCESS on success,
 *          SEC_OP_FAILURE on failure.
 *
 * @param[in]   pub_key                    Payload to be hashed.
 * @param[in]   pub_key_len                Length of payload to be hashed.
 * @param[in]   pri_key                    Payload to be hashed.
 * @param[in]   pri_key_len                Length of payload to be hashed.
 * @param[in]   output_buf                 Pre-allocated buffer where the generated KT will be stored.
 * @param[in]   output_buf_len             Length of output_buf.
 * @param[in]   output_len                 Where the length of KT will be stored upon successful 
 *                                           generation.
 *
 */
typedef int (*sign_on_basic_sec_gen_kt)(const uint8_t *pub_key, uint16_t pub_key_len,
                                                    const uint8_t *pri_key, uint16_t pri_key_len,
                                                    uint8_t *output_buf, uint16_t output_buf_len, 
                                                    uint16_t *output_len);

/**@brief Generic function interface for generating signature of bootstrapping request.
 *
 * @param[in]   pri_key                    Private key used to generate signature.
 * @param[in]   payload                    Payload to be signed.
 * @param[in]   payload_len                Length of payload to be signed.
 * @param[in]   output_buf                 Pre-allocated buffer where generated signature will be stored.
 * @param[in]   output_buf_len             Length of output_buf.
 * @param[in]   output_len                 Variable where length of generated signature will be stored
 *                                           if signature generation is successful.
 *
 */
typedef int (*sign_on_basic_sec_gen_btstrp_rqst_sig)(const uint8_t *pri_key, const uint8_t *payload, 
                                                   uint16_t payload_len, uint8_t *output_buf,  
                                                   uint16_t output_buf_len, uint16_t *output_len);

/**@brief Generic function interface for verifying signature of bootstrapping request response.
 *
 * @param[in]   payload                    Payload over which signature will be verified.
 * @param[in]   payload_len                Length of payload.
 * @param[in]   sig                        Signature to verify.
 * @param[in]   sig_len                    Length of signature to verify.
 * @param[in]   key                        Key to use in verifying signature.
 * @param[in]   key_len                    Length of key.
 *
 */
typedef int (*sign_on_basic_sec_vrfy_btstrp_rqst_rspns_sig)(const uint8_t *payload, uint16_t payload_len,
                                                                const uint8_t *sig, uint16_t sig_len,
                                                                const uint8_t *key, uint16_t key_len);

/**@brief Generic function interface for generating signature of certificate request.
 *
 * @param[in]   pri_key                    Private key used to generate signature.
 * @param[in]   payload                    Payload to be signed.
 * @param[in]   payload_len                Length of payload to be signed.
 * @param[in]   output_buf                 Pre-allocated buffer where generated signature will be stored.
 * @param[in]   output_buf_len             Length of output_buf.
 * @param[in]   output_len                 Variable where length of generated signature will be stored
 *                                           if signature generation is successful.
 *
 */
typedef int (*sign_on_basic_sec_gen_cert_rqst_sig)(const uint8_t *pri_key, const uint8_t *payload, 
                                                   uint16_t payload_len, uint8_t *output_buf,  
                                                   uint16_t output_buf_len, uint16_t *output_len);

/**@brief Generic function interface for verifying signature of certificate request response.
 *
 * @param[in]   payload                    Payload over which signature will be verified.
 * @param[in]   payload_len                Length of payload.
 * @param[in]   sig                        Signature to verify.
 * @param[in]   sig_len                    Length of signature to verify.
 * @param[in]   key                        Key to use in verifying signature.
 * @param[in]   key_len                    Length of key.
 *
 */
typedef int (*sign_on_basic_sec_vrfy_cert_rqst_rspns_sig)(const uint8_t *payload, uint16_t payload_len,
                                                                const uint8_t *sig, uint16_t sig_len,
                                                                const uint8_t *key, uint16_t key_len);

/**@brief Generic function interface for decrypting the encrypted KD private key in the certificate request 
 *          response. Returns SEC_OP_SUCCESS on success, SEC_OP_FAILURE on failure.
 *
 * @param[in]   key                        Key to use for decryption.
 * @param[in]   key_len                    Length of decryption key.
 * @param[in]   encrypted_payload          Encrypted payload to be decrypted. 
 * @param[in]   decrypted_payload          Buffer where decrypted payload will be stored.
 * @param[in]   decrypted_payload_len      Pointer to variable that will be filled with size of decrypted
 *                                           payload upon successful decryption.
 *
 */
typedef int (*sign_on_basic_sec_decrypt_kd_pri)(uint8_t *key, uint16_t key_len, 
                                                              const uint8_t *encrypted_kd_pri, 
                                                              uint16_t encrypted_kd_pri_len,
                                                              uint8_t *decrypted_kd_pri, 
                                                              uint16_t *decrypted_kd_pri_len);

/**@brief Generic function interface for generating signature of finish message.
 *
 * @param[in]   pri_key                    Private key used to generate signature.
 * @param[in]   payload                    Payload to be signed.
 * @param[in]   payload_len                Length of payload to be signed.
 * @param[in]   output_buf                 Pre-allocated buffer where generated signature will be stored.
 * @param[in]   output_buf_len             Length of output_buf.
 * @param[in]   output_len                 Variable where length of generated signature will be stored
 *                                           if signature generation is successful.
 *
 */
typedef int (*sign_on_basic_sec_gen_fin_msg_sig)(const uint8_t *pri_key, const uint8_t *payload, 
                                                   uint16_t payload_len, uint8_t *output_buf,  
                                                   uint16_t output_buf_len, uint16_t *output_len);

/**@brief Structure for holding abstract functions that should be implemented by Sign-on basic variants.
 *          All functions here return SEC_OP_SUCCESS on success and SEC_OP_FAILURE on failure.
 *          See sign-on-basic-sec-consts.h for the actual values.
 *
 * @var         sign_on_basic_sec_gen_sha256_hash                Function to generate a SHA256 hash.
 *
 * @var         sign_on_basic_sec_gen_n1_keypair                 Function to generate N1 key pair.
 *
 * @var         sign_on_basic_sec_gen_kt                         Function to generate KT from the N1 public key
 *                                                                     and N2 private key.
 *
 * @var         sign_on_basic_sec_gen_btstrp_rqst_sig            Function to generate signature for bootstrapping 
 *                                                                     request.
 *
 * @var         sign_on_basic_sec_vrfy_btstrp_rqst_rspns_sig     Function to verify signature of bootstrapping 
 *                                                                     request response.
 *
 * @var         sign_on_basic_sec_gen_cert_rqst_sig              Function to generate signature for certificate 
 *                                                                     request.
 *
 * @var         sign_on_basic_sec_vrfy_cert_rqst_rspns_sig       Function to verify signature of certificate 
 *                                                                     request response.
 *
 * @var         sign_on_basic_sec_decrypt_kd_pri                 Function to decrypt the encrypted KD key pair 
 *                                                                     private key in the certificate request
 *                                                                     response.
 *
 * @var         sign_on_basic_sec_gen_fin_msg_sig                Function to generate signature for finish
 *                                                                     message.
 */
struct sign_on_basic_sec_intf {
  sign_on_basic_sec_gen_sha256_hash gen_sha256_hash;
  sign_on_basic_sec_gen_n1_keypair gen_n1_keypair;
  sign_on_basic_sec_gen_kt gen_kt;
  sign_on_basic_sec_gen_btstrp_rqst_sig gen_btstrp_rqst_sig;
  sign_on_basic_sec_vrfy_btstrp_rqst_rspns_sig vrfy_btstrp_rqst_rspns_sig;
  sign_on_basic_sec_gen_cert_rqst_sig gen_cert_rqst_sig;
  sign_on_basic_sec_vrfy_cert_rqst_rspns_sig vrfy_cert_rqst_rspns_sig;
  sign_on_basic_sec_decrypt_kd_pri decrypt_kd_pri;
  sign_on_basic_sec_gen_fin_msg_sig gen_fin_msg_sig;
};

/**@brief Structure for keeping track of state for a given Sign-on Basic client.
 *
 * @var         KS_pub_p                   "Key shared" public key. This is the public key of a preshared  
 *                                           asymmetric key pair between a Sign-On Basic controller and device.
 * @var         KS_pub_len                 Length of the bootstrapping public key.
 *
 * @var         KS_pri_p                   "Key shared" private key. This is the private key of a preshared 
 *                                           asymmetric key pair between a Sign-On Basic controller and device.
 * @var         KS_pri_len                 Length of the bootstrapping private key.
 *
 * @var         device_identifier_p        The device identifier, a unique sequence of bytes that a Sign-on  
 *                                           Basic controller can use to identify this device. 
 * @var         device_identifier_len      Length of the device identifier.
 *
 * @var         device_capabilities_p      The device capabilities, a sequence of bytes that lets the Sign-on  
 *                                           Basic Controller know what the device is capable of (i.e. can  
 *                                           do temperature readings, can detect motion, etc).                                        
 * @var         device_capabilities_len    Length of the device capabilities.
 *
 * @var         secure_sign_on_code_p      The secure sign on code, a pre-shared secret between the device and                 
 *                                           controller used as a symmetric key.
 * @var         secure_sign_on_code_len    Length of the secure sign on code.
 *
 * @var         KT_p                       "Key temporal". This is the "temporal" symmetric key negotiated through 
 *                                         diffie hellman during the sign-on. It is temporal because it is only used
 *                                         during the sign-on exchange during which it was created.
 * @var         KT_len                     Length of KT.
 *
 * @var         N1_pub_p                   The public key generated by the device for diffie hellman during sign-on.
 * @var         N1_pub_len                 Length of N1_pub.
 *
 * @var         N1_pri_p                   The private key generated by the device for diffie hellman during sign-on.
 * @var         N1_pri_len                 Length of N1_pri.
 *
 * @var         N2_pub_p                   The public key generated by the controller for diffie hellman during sign-on.
 * @var         N2_pub_len                 Length of N2_pub.
 *
 * @var         trust_anchor_cert_p        The certificate of the trust anchor's key. 
 * @var         trust_anchor_cert_len      Length of the trust anchor certificate.
 *
 * @var         KD_pub_cert_p              "Key Device" public key certificate. This is the certificate of the 
 *                                           public key that the controller generates for the device.
 * @var         KD_pub_cert_len            Length of the KD public key certificate.
 *
 * @var         KD_pri_p                   The private key of the "Key Device" key pair generated by the controller
 *                                           for the device.
 * @var         KD_pri_len                 Length of the KD private key.
 *
 * @var         sec_intf                   This structure provides function pointers to do security operations for this
 *                                           instance of Sign-on Basic client. This will change depending on the 
 *                                           variant that is selected.
 *
 * @var         status                     This is the status of the sign on client. See sign-on-basic-client-consts.h for
 *                                           the possible states here.
 */
struct sign_on_basic_client_t {

  uint8_t KS_pub_p[SIGN_ON_BASIC_CLIENT_KS_PUB_MAX_LENGTH];
  uint16_t KS_pub_len;

  uint8_t KS_pri_p[SIGN_ON_BASIC_CLIENT_KS_PRI_MAX_LENGTH];
  uint16_t KS_pri_len;

  uint8_t device_identifier_p[SIGN_ON_BASIC_CLIENT_DEVICE_IDENTIFIER_MAX_LENGTH];
  uint16_t device_identifier_len;

  uint8_t device_capabilities_p[SIGN_ON_BASIC_CLIENT_DEVICE_CAPABILITIES_MAX_LENGTH];
  uint16_t device_capabilities_len;

  uint8_t secure_sign_on_code_p[SIGN_ON_BASIC_CLIENT_SECURE_SIGN_ON_CODE_MAX_LENGTH];
  uint16_t secure_sign_on_code_len;

  uint8_t KT_p[SIGN_ON_BASIC_CLIENT_KT_MAX_LENGTH];
  uint16_t KT_len;

  uint8_t N1_pub_p[SIGN_ON_BASIC_CLIENT_N1_PUB_MAX_LENGTH];
  uint16_t N1_pub_len;

  uint8_t N1_pri_p[SIGN_ON_BASIC_CLIENT_N1_PRI_MAX_LENGTH];
  uint16_t N1_pri_len;

  uint8_t N2_pub_p[SIGN_ON_BASIC_CLIENT_N2_PUB_MAX_LENGTH];
  uint16_t N2_pub_len;

  uint8_t trust_anchor_cert_p[SIGN_ON_BASIC_CLIENT_TRUST_ANCHOR_CERT_MAX_LENGTH];
  uint16_t trust_anchor_cert_len;

  uint8_t KD_pub_cert_p[SIGN_ON_BASIC_CLIENT_KD_PUB_CERT_MAX_LENGTH];
  uint16_t KD_pub_cert_len;

  uint8_t KD_pri_p[SIGN_ON_BASIC_CLIENT_KD_PRI_MAX_LENGTH];
  uint16_t KD_pri_len;

  uint8_t status;

  struct sign_on_basic_sec_intf sec_intf;

};

/**@brief Result of calling sign_on_basic_client_init.
 */
enum sign_on_basic_client_init_result {
  SIGN_ON_BASIC_CLIENT_INIT_SUCCESS,
  SIGN_ON_BASIC_CLIENT_INIT_FAILED_UNRECOGNIZED_VARIANT,
  SIGN_ON_BASIC_CLIENT_INIT_FAILED_TO_SET_SEC_INTF,
};

/**@brief Function to initialize state for a sign_on_basic_client_t. All buffers passed 
 *        in will be copied into the sign_on_basic_client basic client.
 *
 * @param[in]   variant                    This is the variant of the Sign-On basic protocol that you
 *                                           want to initialize. This will change the function pointers that 
 *                                           are passed to sign_on_basic_sec_intf to do security related
 *                                           operations, like signature generation.
 *                                         See secure-sign-on-basic-consts.h for all of the variants, as  
 *                                           well as descriptions.
 * @param[in]   sign_on_basic_client   Reference to the sign_on_basic_client_t to be initialized.
 * @param[in]   device_identifier_p        See the sign_on_basic_client_t documentation.
 * @param[in]   device_identifier_len      "                                               "
 * @param[in]   device_capabilities_p      "                                               "                                       
 * @param[in]   device_capabilities_len    "                                               "
 * @param[in]   secure_sign_on_code_p      "                                               "
 * @param[in]   KS_pub_p                   "                                               "
 * @param[in]   KS_pub_len                 "                                               "
 * @param[in]   KS_pri_p                   "                                               "
 * @param[in]   KS_pri_len                 "                                               "
 *
 */
enum sign_on_basic_client_init_result sign_on_basic_client_init(
                              uint8_t variant,
                              struct sign_on_basic_client_t *sign_on_basic_client,
                              const uint8_t *device_identifier_p, uint16_t device_identifier_len,
                              const uint8_t *device_capabilities_p, uint16_t device_capabilities_len,
                              const uint8_t *secure_sign_on_code_p,
                              const uint8_t *KS_pub_p, uint16_t KS_pub_len,
                              const uint8_t *KS_pri_p, uint16_t KS_pri_len);

/**@brief Result of calling cnstrct_btstrp_rqst_result.
 */
enum cnstrct_btstrp_rqst_result {
  CNSTRCT_BTSTRP_RQST_SUCCESS,
  CNSTRCT_BTSTRP_RQST_BUFFER_TOO_SHORT,
  CNSTRCT_BTSTRP_RQST_FAILED_TO_GENERATE_N1_KEYPAIR,
  CNSTRCT_BTSTRP_RQST_FAILED_TO_GENERATE_SIG_PAYLOAD_HASH,
  CNSTRCT_BTSTRP_RQST_FAILED_TO_GENERATE_SIG,
};

/**@brief Function to construct a bootstrapping request.
 *        For a given sign on exchange:
 *          Should be called after sign_on_basic_client_init. 
 *          Should be called before prcs_btstrp_rqst_rspns, cnstrct_cert_rqst, and prcs_cert_rqst_rspns.
 *
 * @param[in]   buf_p                      Pre allocated buffer to use in generating bootstrapping request.
 * @param[in]   buf_len                    Length of pre allocated buffer.
 * @param[in]   output_len_p               Pointer to variable that will be filled with length of generated
 *                                         bootstrapping request upon successful construction.
 * @param[in]   sign_on_basic_client   Reference to the sign_on_basic_client_t to use in construction.
 */
enum cnstrct_btstrp_rqst_result cnstrct_btstrp_rqst(uint8_t *buf_p, uint16_t buf_len,
                              uint16_t *output_len_p,
                              struct sign_on_basic_client_t *sign_on_basic_client);

/**@brief Result of calling prcs_btstrp_rqst_rspns_result.
 */
enum prcs_btstrp_rqst_rspns_result {
  PRCS_BTSTRP_RQST_RSPNS_SUCCESS,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_VERIFY_SIGNATURE,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_PACKET_HEADER,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_SIG,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_TRUST_ANCHOR_CERT,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_N2_PUB,
  PRCS_BTSTRP_RQST_RSPNS_FAILED_TO_GENERATE_KT,
};

/**@brief Function to process a bootstrapping request response. 
 *        For a given sign on exchange:
 *          Should be called after sign_on_basic_client_init and prcs_btstrp_rqst_rspns. 
 *          Should be called before cnstrct_cert_rqst, and prcs_cert_rqst_rspns.
 *
 * @note  Calling this function will not modify any state of the sign on basic client that it is passed
 *          until after it successfully processes the entire bootstrapping request response.
 *
 * @param[in]   btstrp_rqst_rspns_buf_p    Buffer that holds the bootstrapping request response.
 * @param[in]   btstrp_rqst_rspns_buf_len  Length of the bootstrapping request response.
 * @param[in]   sign_on_basic_client   Reference to the sign_on_basic_client_t to modify while processing.
 */
enum prcs_btstrp_rqst_rspns_result prcs_btstrp_rqst_rspns(const uint8_t *btstrp_rqst_rspns_buf_p,
                                    uint16_t btstrp_rqst_rspns_buf_len,
                                    struct sign_on_basic_client_t *sign_on_basic_client);

/**@brief Result of calling cnstrct_cert_rqst_result.
 */
enum cnstrct_cert_rqst_result {
  CNSTRCT_CERT_RQST_SUCCESS,
  CNSTRCT_CERT_RQST_BUFFER_TOO_SHORT,
  CNSTRCT_CERT_RQST_FAILED_TO_GENERATE_N2_PUB_HASH,
  CNSTRCT_CERT_RQST_FAILED_TO_GENERATE_TRUST_ANCHOR_CERT_HASH,
  CNSTRCT_CERT_RQST_FAILED_TO_GENERATE_SIG_PAYLOAD_HASH,
  CNSTRCT_CERT_RQST_FAILED_TO_GENERATE_SIG,
};

/**@brief Function to construct a certificate request.
 *        For a given sign on exchange:
 *          Should be called after sign_on_basic_client_init, and prcs_btstrp_rqst_rspns.
 *          Should be called before prcs_cert_rqst_rspns.
 *
 * @param[in]   buf_p                      Pre allocated buffer to use in generating certificate request.
 * @param[in]   buf_len                    Length of pre allocated buffer.
 * @param[in]   output_len_p               Pointer to variable that will be filled with length of generated
 *                                         certificate request upon successful construction.
 * @param[in]   sign_on_basic_client   Reference to the sign_on_basic_client_t to use in construction.
 */
enum cnstrct_cert_rqst_result cnstrct_cert_rqst(uint8_t *buf_p, uint16_t buf_len, uint16_t *output_len_p,
                            struct sign_on_basic_client_t *sign_on_basic_client);

/**@brief Result of calling prcs_cert_rqst_rspns_result.
 */
enum prcs_cert_rqst_rspns_result {
  PRCS_CERT_RQST_RSPNS_SUCCESS,
  PRCS_CERT_RQST_RSPNS_FAILED_TO_VERIFY_SIGNATURE,
  PRCS_CERT_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_PACKET_HEADER,
  PRCS_CERT_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_KD_PUB_CERT,
  PRCS_CERT_RQST_RSPNS_FAILED_TO_GET_TLV_VAL_KD_PRI_ENC,
  PRCS_CERT_RQST_RSPNS_FAILED_TO_DECRYPT_KD_PRI
};

/**@brief Function to process a certificate request response. 
 *        For a given sign on exchange:
 *          Should be called after sign_on_basic_client_init, prcs_btstrp_rqst_rspns, and cnstrct_cert_rqst.
 *          Should be called before cnstrct_fin_msg.
 *
 * @note  Calling this function will not modify any state of the sign on basic client that it is passed
 *          until after it successfully processes the entire certificate request response.
 *
 * @param[in]   cert_rqst_rspns_buf_p      Buffer that holds the certificate request response.
 * @param[in]   cert_rqst_rspns_buf_len    Length of the certificate request response.
 * @param[in]   sign_on_basic_client       Reference to the sign_on_basic_client_t to modify while processing.
 */
enum prcs_cert_rqst_rspns_result prcs_cert_rqst_rspns(const uint8_t *cert_rqst_rspns_buf_p,
                                  uint16_t cert_rqst_rspns_buf_len,
                                  struct sign_on_basic_client_t *sign_on_basic_client);

/**@brief Result of calling cnstrct_fin_msg_result.
 */
enum cnstrct_fin_msg_result {
  CNSTRCT_FIN_MSG_SUCCESS,
  CNSTRCT_FIN_MSG_BUFFER_TOO_SHORT,
  CNSTRCT_FIN_MSG_FAILED_TO_GENERATE_SIG_PAYLOAD_HASH,
  CNSTRCT_FIN_MSG_FAILED_TO_GENERATE_SIG,
};

/**@brief Function to construct a sign-on basic finish message (this lets the controller know sign-on was completed
 *          successfully.
 *        For a given sign on exchange:
 *          Should be called after sign_on_basic_client_init, prcs_btstrp_rqst_rspns, cnstrct_cert_rqst,
 *            and prcs_cert_rqst_rspns.
 *          Should be called last in the sign-on process.
 *
 * @param[in]   buf_p                      Pre allocated buffer to use in generating finish message.
 * @param[in]   buf_len                    Length of pre allocated buffer.
 * @param[in]   output_len_p               Pointer to variable that will be filled with length of generated
 *                                         finish message upon successful construction.
 * @param[in]   sign_on_basic_client   Reference to the sign_on_basic_client_t to use in construction.
 */
enum cnstrct_fin_msg_result cnstrct_fin_msg(uint8_t *buf_p, uint16_t buf_len, uint16_t *output_len_p,
                            struct sign_on_basic_client_t *sign_on_basic_client);

#endif // SIGN_ON_BASIC_CLIENT_H