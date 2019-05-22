package com.avernakis.message.bus;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * The type Async message bus.
 */
public class AsyncMessageBus extends MessageBus implements Runnable {
  /**
   * Instantiates a new Async message bus.
   */
  AsyncMessageBus(int sleepMs) {
    asyncThread = new Thread(this);
    messageQueue = new ConcurrentLinkedQueue<>();
    handlerMap = new ConcurrentHashMap<>();

    this.sleepMs = sleepMs;
  }

  /**
   * Start.
   */
  public void start() { asyncThread.run(); }

  @Override
  public void run() {
    while (!Thread.currentThread().isInterrupted()) {
      processMessage();
      try {
        Thread.sleep(sleepMs);
      } catch (InterruptedException e) {
        break;
      }
    }
  }

  /**
   * Stop.
   */
  public void stop() {
    asyncThread.interrupt();
  }

  private Thread asyncThread;
  private int sleepMs;
}
