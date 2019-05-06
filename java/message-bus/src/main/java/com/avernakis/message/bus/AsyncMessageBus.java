package com.avernakis.message.bus;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class AsyncMessageBus extends MessageBus {
  AsyncMessageBus() {
    messageQueue = new ConcurrentLinkedQueue<>();
    handlerMap = new ConcurrentHashMap<>();
  }
}
