#if defined _inline_timers_included
    #endinput
#endif
#define _inline_timers_included

#include <a_samp>
#include <YSI\y_malloc>
#include <YSI\y_inline>

forward InlineTimersHandler(repeat, address, pointer, offset, data1, data2, Alloc: mem);
public InlineTimersHandler(repeat, address, pointer, offset, data1, data2, Alloc: mem) 
{
    new 
        cb_data[E_CALLBACK_DATA]
    ;

    cb_data[E_CALLBACK_DATA_ALLOC]      = ResolvedAlloc: address;
    cb_data[E_CALLBACK_DATA_POINTER]    = Function: pointer;
    cb_data[E_CALLBACK_DATA_OFFSET]     = offset;
    cb_data[E_CALLBACK_DATA_FORMAT][0]  = data1;
    cb_data[E_CALLBACK_DATA_FORMAT][1]  = data2;

    Callback_Call(cb_data);

    if (!repeat) {
        free(Alloc: mget(Alloc: mem, 1));
        free(Alloc: mem);
    }

    return true;
}


stock SetInlineTimer(callback: callback, delay, repeat)
{
    new 
        cb_data[E_CALLBACK_DATA],
        Alloc: mem = malloc(2)
    ;

    if (!Callback_Get(callback, cb_data)) {
        return false;
    }
	
    if (mem == NO_ALLOC) {
        Callback_Release(cb_data);
        return false;
    }

    new 
        timer = SetTimerEx("InlineTimersHandler", delay, repeat, "iiiiiii", repeat, _: cb_data[E_CALLBACK_DATA_ALLOC], _: cb_data[E_CALLBACK_DATA_POINTER], cb_data[E_CALLBACK_DATA_OFFSET], cb_data[E_CALLBACK_DATA_FORMAT][0], cb_data[E_CALLBACK_DATA_FORMAT][1], _: mem)
    ;

    mset(mem, 0, timer);
    mset(mem, 1, _: cb_data[E_CALLBACK_DATA_ALLOC]);
    
    return _: mem;
}

stock KillInlineTimer(timer)
{
    KillTimer(mget(Alloc: timer, 0));

    free(Alloc: mget(Alloc: timer, 1));
    free(Alloc: timer);

    return true;
}  