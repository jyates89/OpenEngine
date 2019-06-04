package com.avernakis.openengine.message.bus;

import org.junit.jupiter.api.*;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.mockito.junit.jupiter.MockitoExtension;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class MessageBusTest {
  class TestMessage implements Message {
    @Override
    public String description() {
      return "TestMessage";
    }
  }
  class TestHandler extends Handler<TestMessage> {
    @Override
    TestMessage callback(TestMessage message) {
      return null;
    }
  }

  @BeforeEach
  void init() {
    handler = new TestHandler();
    asyncMessageBus = new SyncMessageBus(10);
  }

  @Test
  @DisplayName("New message type and handler can be registered.")
  void newTypeAndHandlerCanBeRegistered() {
    asyncMessageBus.registerHandler(TestMessage.class, handler);
    assertTrue(asyncMessageBus.handlerMap.get(TestMessage.class).contains(handler));
  }

  @Test
  @DisplayName("Attempting to register the same handler twice results in error.")
  void duplicateHandlerCannotBeRegistered() {
    asyncMessageBus.registerHandler(TestMessage.class, handler);
    RuntimeException exception = assertThrows(RuntimeException.class,
        () -> asyncMessageBus.registerHandler(TestMessage.class, handler));
    assertEquals(exception.getMessage(), "handler already registered");
  }

  @Test
  @DisplayName("Pushing a message of registered type onto the bus does not throw.")
  void messagesCanBePushed() {
    asyncMessageBus.registerHandler(TestMessage.class, handler);

    TestMessage testMessage = new TestMessage();
    asyncMessageBus.submitMessage(testMessage);
    assertTrue(asyncMessageBus.messageQueue.contains(testMessage));
  }

  @ParameterizedTest
  @ValueSource(ints = {1, 2, 3})
  @DisplayName("Message handlers for message type are called.")
  void messageHandlerCalled(int messageCount) {
    TestHandler testHandler = mock(TestHandler.class);
    TestMessage testMessage = new TestMessage();

    asyncMessageBus.registerHandler(TestMessage.class, testHandler);
    int messagesSent = 0;
    while (messagesSent++ < messageCount) {
      asyncMessageBus.submitMessage(testMessage);
    }
    asyncMessageBus.processMessages();

    verify(testHandler, times(messageCount)).callback(testMessage);
  }

  @Test
  @DisplayName("Result can be pushed onto queue after event is handled.")
  void resultsCanBeGenerated() {
    TestHandler testHandler = mock(TestHandler.class);
    TestMessage testMessage = new TestMessage();

    // Only return new message when called with the original TestMessage.
    when(testHandler.callback(testMessage)).thenReturn(new TestMessage());

    asyncMessageBus.registerHandler(TestMessage.class, testHandler);
    asyncMessageBus.submitMessage(testMessage);
    asyncMessageBus.processMessages();

    // It should be called twice as it result message is pushed onto the
    // queue by the handler of the initial message.
    verify(testHandler, times(2)).callback(any());
  }

  @Test
  @DisplayName("Events can be handled and then the result ignored.")
  void eventsCanBeHandledThenIgnored() {

  }

  private TestHandler handler;
  private SyncMessageBus asyncMessageBus;
}
