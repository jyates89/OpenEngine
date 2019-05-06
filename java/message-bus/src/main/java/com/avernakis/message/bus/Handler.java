package com.avernakis.message.bus;

abstract class Handler<T extends Message> {
  // Return values are covariant; we can return any
  // subclass of Message.
  abstract Message callback(T message);
}
