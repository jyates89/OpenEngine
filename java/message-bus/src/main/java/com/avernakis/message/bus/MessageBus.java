package com.avernakis.message.bus;

import java.util.*;

abstract class MessageBus {
  Queue<Message> messageQueue;
  Map<Class<? extends Message>, List<Handler>> handlerMap;

  <T extends Message> void registerHandler(Class<T> type, Handler<T> handler) {
    if (handlerMap.containsKey(type)) {
      if (handlerMap.get(type).contains(handler)) {
        throw new RuntimeException("handler already registered");
      }
    }
    handlerMap.computeIfAbsent(type, x -> new LinkedList<>()).add(handler);
  }

  void submitMessage(Message message) {
    if (!handlerMap.containsKey(message.getClass())) {
      throw new RuntimeException("message type has no registered handlers");
    }
    messageQueue.offer(message);
  }

  void processMessage() {
    Message message = messageQueue.peek();
    if (message != null && handlerMap.containsKey(message.getClass())) {

      for (Handler handler: handlerMap.get(message.getClass())) {
        // We know get will only ever return handlers for the type that is specified in the message. We can't get type
        // information at runtime because of type erasure, but, given the previous statement is true, this is safe. The
        // handler registration signature prevents anything else.
        @SuppressWarnings("unchecked")
        Message result = handler.callback(message);
        if (result != null) messageQueue.offer(result);
      }
    }
  }
}
