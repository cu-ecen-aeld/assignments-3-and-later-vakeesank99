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
    usleep(thread_func_args->wait_to_obtain_ms *1000);
    int rc = pthread_mutex_lock(&thread_func_args->mutex);
    if (rc!=0){
        ERROR_LOG("pthread_mutex_lock failed with %d\n",rc);
        thread_func_args->thread_complete_success = false;
        return NULL;
        
    } 
    usleep(thread_func_args->wait_to_release_ms *1000);
    rc = pthread_mutex_unlock(&thread_func_args->mutex);
    if (rc!=0){
            ERROR_LOG("pthread_mutex_unlock failed with %d\n",rc);
            thread_func_args->thread_complete_success = false;
    }
    thread_func_args->thread_complete_success=true;
    return NULL;
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
        data->thread_complete_success = false;
        goto out;
    }

    // struct thread_data *data; 

    // setup mutex
    pthread_mutex_init(&data->mutex,NULL);
    data->wait_to_obtain_ms=wait_to_obtain_ms;
    data->wait_to_release_ms=wait_to_release_ms;

    //start thread
    int rc = pthread_create(thread, NULL, threadfunc, (void*) &data);
    if (rc!=0){
        ERROR_LOG("pthread_create failed with %d\n",rc);
        data->thread_complete_success = false;
        goto out;
    }
    DEBUG_LOG("join done\n");
    rc=pthread_join(*thread,NULL);
   
    if (rc!=0){
        ERROR_LOG("pthread_join thread %u failed with %d\n",(unsigned int )*thread,rc);
        data->thread_complete_success = false;
    }
    goto out;
out:
    free(data);

    return data->thread_complete_success;
}

