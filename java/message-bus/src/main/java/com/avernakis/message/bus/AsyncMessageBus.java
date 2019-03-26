package com.avernakis.message.bus;

import java.util.concurrent.ConcurrentLinkedQueue;

public class AsyncMessageBus extends MessageBus {
  AsyncMessageBus() {
    messageQueue = new ConcurrentLinkedQueue<>();
  }


  <T extends Message> T pull() {
    return messageQueue.poll();
  }
}
