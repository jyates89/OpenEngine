package com.avernakis.message.bus;

import java.util.Queue;

abstract class MessageBus {
  Queue<?> messageQueue;

  abstract <T extends Message> void push(T message);

}
