# inline_timers

[![sampctl](https://shields.southcla.ws/badge/sampctl-inline--timers-2f2f2f.svg?style=for-the-badge)](https://github.com/ltkarim/inline-timers)

This include allows you to use inline functions as callbacks for timers, similiar to inline dialog callbacks and inline MySQL callbacks. 

There is no support for passing extra arguments through this, because the variables (and arguments) in the parent function are accessible in the inline function as well due to a feature called "closuers", thus rendering the usage of the extra arguments useless. This is however a feature of YSI itself and it has nothing to do with this include.



## Installation

Simply install to your project:

```bash
sampctl package install ltkarim/inline-timers
```

Include in your code and begin using the library:

```pawn
#include <inline_timers>
```

## Usage

#### <a name="SetInlineTimer">SetInlineTimer`(callback: callback, delay, repeat)`</a>
>* **Parameters:**
>    * `callback`: The inline callback to use.
>    * `delay`: The interval of the timer in milliseconds.
>    * `repeat`: whether the timer should repeat or not.
>* **Returns:**
>    * `false` on failure, `ID` to be used with `KillInlineTimer` on success.

Starts a timer with the specified interval.

**NOTE:** This function does NOT return the timer ID, rather the malloc address that contains the timer ID and callback data. You can't use ``KillTimer`` to kill it!

***

#### <a name="KillInlineTimer">KillInlineTimer`(timer)`</a>
>* **Parameters:**
>    * `timer`: The timer ID returned by `SetInlineTimer`.
>* **Returns:**
>    * `true` regardless of the result.

Stops the specified timer.

**NOTE:** Inline timers have to be killed with the above function since it allocates extra memory that need to be freed.

***

Example:

```pawn
new 
    someInt = 1337,
    someStr[] = "hello world",
    Float: someFloat = 1.337
;

inline TimerTest()
{
    printf(" TimerTest called after 3 seconds! %i, %s, %0.3f", someInt, someStr, someFloat);
}
SetInlineTimer(using inline TimerTest, 3000, false);
```

Outputs:

```
 TimerTest called! 1337, hello world, 1.337
```

## Dependencies

* [YSI](https://github.com/pawn-lang/YSI-Includes) 
    * y_malloc
    * y_inline

## Testing

To test, simply run the package:

```bash
sampctl package run
```

## Credits

* [Y_Less](https://github.com/Y-Less)
    * [YSI library](https://github.com/pawn-lang/YSI-Includes)
    * [This post from years ago that this include is based of.](http://forum.sa-mp.com/showpost.php?p=2279564&postcount=7)
