package com.avernakis.message.bus;

import java.util.HashMap;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;

public class SyncMessageBus extends MessageBus implements Runnable {
  SyncMessageBus() {
    messageQueue = new LinkedBlockingQueue<>();
    handlerMap = new HashMap<>();
  }

  SyncMessageBus(int queueLimit) {
    if (queueLimit == 1) {
      messageQueue = new SynchronousQueue<>();
    } else {
      messageQueue = new ArrayBlockingQueue<>(queueLimit);
    }
    handlerMap = new HashMap<>();
  }

  @Override
  public void run() {
    processMessage();
  }
}
