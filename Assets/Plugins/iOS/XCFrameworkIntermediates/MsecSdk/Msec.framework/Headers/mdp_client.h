/*  =====================================================================
 *  mdcliapi.h - Majordomo Protocol Client API
 *  Implements the MDP/Worker spec at http://rfc.zeromq.org/spec:7.
 *  ===================================================================== */

#ifndef __MDP_CLIENT_H_INCLUDED__
#define __MDP_CLIENT_H_INCLUDED__

#include <pthread.h>
#include "czmq.h"
#include "mdp.h"
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_ASYNC_NUM_MSG_HANDLERS 5
#define ENV_ZSYS_THREAD_NAME_PREFIX_STR "ZSYS_THREAD_NAME_PREFIX_STR=MsecSys"
#define MAX_BROKERS_PER_CLIENT 4


//  Structure of our class
//  We access these properties only via class methods
typedef struct appdata{
    char* package_name;
    char* device_id;
    char* framework_name;
    char* sdk_name;
    char* sdk_version;
} appdata_t;

typedef struct _mdcli_msg_t {
    zmsg_t* msg;
    int retries;
    int64_t last_sending_timestamp;
    char* uuid;
} mdcli_msg_t;

struct _mdcli_t {
    void *ctx;                //  Our context
    char *broker;
    char *arr_brokers[MAX_BROKERS_PER_CLIENT];
    int arr_broker_index;
    int arr_broker_len;
    void *broker_client;               //  Socket to g_broker
    void *handlers;
    void *sender;
    int verbose;                //  Print activity to stdout
    int timeout;                //  Request timeout
    int retries;                //  Request retries
    zhashx_t * async_pending_msg_hash;
    pthread_t async_msg_handler_threads[MAX_ASYNC_NUM_MSG_HANDLERS];
    pthread_t async_msg_main_thread;
    bool curve_support;
    char* curve_publickey;
    char* curve_secretkey;
    char* curve_serverkey;
    appdata_t appdata;
    bool async;
};
//  Opaque class structure
typedef struct _mdcli_t mdcli_t;

enum mdcli_errno {
    MDP_NAN = 0,
    MDP_SUCCESS = 1,
    MDP_ASYNC_THROTTLING = 2,
};


// Plan configuration struct
enum sec_plan_type {
    UNKNOWN_DETECTION_PLAN = 0,
    ONSITE_DETECTION_PLAN = 1,
    REMOTE_DETECTION_PLAN = 2,
};

// Plan configuration
__attribute((__annotate__(("strenc"))))
typedef struct _sec_plan_configuration {
    enum sec_plan_type plan_type;
    int device_info_updating_interval_ms;
    int device_session_key_renewing_interval_s;
    bool onsite_violation_handling;
    bool memory_hooking_detection;
    bool app_integrity_detection;
    bool performance_stats_collection;
} sec_plan_configuration_t;

// Init all static enironments and variables
void mdcli_init(void);

mdcli_t *
    mdcli_new (char *broker, int verbose, bool curve_support, char* curve_publickey, char* curve_secretkey, char* curve_serverkey,
               char* package_name, char* device_id, char* framework_name,
                                  char* sdk_name,
                                  char* sdk_version);
void
    mdcli_set_appdata (mdcli_t *self,  char* package_name, char* device_id, char* framework_name,
                       char* sdk_name,
                       char* sdk_version);
void
    mdcli_destroy (mdcli_t **self_p);
void
    mdcli_set_timeout (mdcli_t *self, int timeout);
void
    mdcli_set_retries (mdcli_t *self, int retries);
zmsg_t *
    mdcli_send (mdcli_t *self, char *service, zmsg_t **request_p);
void
    mdcli_test (char* broker, char* service);
void
    mdcli_session_test (mdcli_t* session);
void
    mdcli_session_send_mem(mdcli_t *session, char *service, unsigned char *mem, int mlen);

int mdcli_session_verify_domain_certificate(mdcli_t* mdp_cli_session, char* domain, int port, int timeout_ms, bool secure);
int mdcli_session_authenticate_device(mdcli_t *mdp_cli_session, char **authentication_ticket, sec_plan_configuration_t *plan_configuration,
                                      bool secure);
bool mdcli_session_send_security_info(mdcli_t* mdp_cli_session, char *device_info, bool secure);
mdcli_t *
mdcli_async_new (char *broker, int verbose, bool curve_support, char *curve_publickey, char *curve_secretkey, char *curve_serverkey);

int
mdcli_async_send (void *ctx, char *service, zmsg_t **request_p);
zmsg_t *
mdcli_async_recv (mdcli_t *self);

void mdcli_msg_destroy(void **pp_mdcli_msg);
void mdcli_async_start(mdcli_t *self);
void mdcli_async_msg_handler(void *ctx);

#ifdef __cplusplus
}
#endif

#endif
