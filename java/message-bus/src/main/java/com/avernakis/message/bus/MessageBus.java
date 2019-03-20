package com.avernakis.message.bus;

import java.util.Queue;

class MessageBus {
  protected Queue<? extends Message> messageQueue;
}
