# TickTack

A library that allows to count ticks and persist them in disk

## Prerequisites

```
cmake
c++11 compiler
pthreads
```

## Getting started

To start using the project instantiate a TickTackStore, it will allow you to create new counters that will be persisted on disk!

### Class::TickTackStore

It provides access to different counters stored in a disk file.

``getOrCreate()``  use it to create a new counter

### Class::Counter

It keeps track of the ticks, don't worry it is thread safe. Its can store up to 18,446,744,073,709,551,615 ticks (or tacks)

Use the operator ``++`` to access this feature!