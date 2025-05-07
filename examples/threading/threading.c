#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
// #define DEBUG_LOG(msg,...)
#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    // pthread_mutex_init(thread_func_args->mutex,NULL);
    // printf("\n----- %d -----\n",thread_func_args->wait_to_obtain_ms);
    usleep(thread_func_args->wait_to_obtain_ms *1000);
    int rc = pthread_mutex_lock(thread_func_args->mutex);
    if (rc!=0){
        ERROR_LOG("pthread_mutex_lock failed with %d\n",rc);
        thread_func_args->thread_complete_success = false;
        // pthread_exit((void *)thread_func_args);
        // return NULL;
        return thread_param;
        
    } 
    usleep(thread_func_args->wait_to_release_ms *1000);
    rc = pthread_mutex_unlock(thread_func_args->mutex);
    if (rc!=0){
            ERROR_LOG("pthread_mutex_unlock failed with %d\n",rc);
            thread_func_args->thread_complete_success = false;
            // return (void *)thread_func_args;
            return thread_param;
            // pthread_exit((void *)thread_func_args);
        }
    thread_func_args->thread_complete_success=true;
    // pthread_exit((void *)thread_func_args);
    // rc=pthread_join(*thread_func_args->thread,NULL);
    // if (rc!=0){
    //     ERROR_LOG("pthread_join thread failed with %d\n",rc);
    //     thread_func_args->thread_complete_success = false;
    // }
    return thread_param;
    // return (void *)thread_func_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     
    //allocate mem for thread_data
    struct thread_data *data;
    data=(struct thread_data *)malloc(sizeof(struct thread_data));
  
    if (data ==NULL){
        ERROR_LOG("heap allocation failed\n");
        // data->thread_complete_success = false;
        return false;
        // goto out;
    }

    // struct thread_data *data2; 

    // setup mutex
    data->mutex = mutex;
    data->wait_to_obtain_ms=wait_to_obtain_ms;
    data->wait_to_release_ms=wait_to_release_ms;
    data->thread_complete_success = false;

    //start thread
    int rc = pthread_create(thread, NULL, threadfunc, (void*)data);
    if (rc!=0){
        ERROR_LOG("pthread_create failed with %d\n",rc);
        // data->thread_complete_success = false;
        return false;
    }
    // data->thread_complete_success = true;
    // rc=pthread_join(*thread,NULL);
    // if (rc!=0){
    //     ERROR_LOG("pthread_join thread failed with %d\n",rc);
    //     goto out;
    //     // data->thread_complete_success = false;
    // }
//     DEBUG_LOG("###############   %d ##############\n",data->thread_complete_success);
//     return data->thread_complete_success;
// out:
    // free(data);
    return true;
    // return data->thread_complete_success;
    // return false;
}

