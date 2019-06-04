package com.avernakis.openengine.message.bus;

import java.util.HashMap;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;

/**
 * The type Sync message bus.
 */
public class SyncMessageBus extends MessageBus {
  /**
   * Instantiates a new Sync message bus.
   */
  SyncMessageBus() {
    messageQueue = new LinkedBlockingQueue<>();
    handlerMap = new HashMap<>();
  }

  /**
   * Instantiates a new Sync message bus.
   *
   * @param queueLimit the queue limit
   */
  SyncMessageBus(int queueLimit) {
    if (queueLimit == 1) {
      messageQueue = new SynchronousQueue<>();
    } else {
      messageQueue = new ArrayBlockingQueue<>(queueLimit);
    }
    handlerMap = new HashMap<>();
  }
}
