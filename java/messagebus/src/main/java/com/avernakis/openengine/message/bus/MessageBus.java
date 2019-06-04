package com.avernakis.openengine.message.bus;

import java.util.*;

/**
 * The type Message bus.
 */
abstract class MessageBus {
  /**
   * The Message queue.
   */
  Queue<Message> messageQueue;
  /**
   * The Handler map.
   */
  Map<Class<? extends Message>, List<Handler>> handlerMap;

  /**
   * Register handler.
   *
   * @param <T>     the type parameter
   * @param type    the type
   * @param handler the handler
   */
  final <T extends Message> void registerHandler(Class<T> type, Handler<T> handler) {
    if (handlerMap.containsKey(type)) {
      if (handlerMap.get(type).contains(handler)) {
        throw new RuntimeException("handler already registered");
      }
    }
    handlerMap.computeIfAbsent(type, x -> new LinkedList<>()).add(handler);
  }

  /**
   * Submit message.
   *
   * @param message the message
   */
  final void submitMessage(Message message) {
    if (!handlerMap.containsKey(message.getClass())) {
      throw new RuntimeException("message type has no registered handlers");
    }
    messageQueue.offer(message);
  }

  /**
   * Process message.
   */
  final void processMessage() {
    Message message = messageQueue.poll();
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

  /**
   * Process messages.
   */
  final void processMessages() {
    while (!messageQueue.isEmpty()) {
      processMessage();
    }
  }
}
