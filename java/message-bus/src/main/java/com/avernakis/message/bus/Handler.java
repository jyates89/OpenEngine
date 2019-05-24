package com.avernakis.message.bus;

/**
 * The type Handler.
 *
 * @param <T> the type parameter
 */
public abstract class Handler<T extends Message> {
  /**
   * Callback message.
   *
   * Return values are covariant; we can return any
   * subclass of Message.
   *
   * @param message the message
   * @return the message
   */
  abstract Message callback(T message);
}
