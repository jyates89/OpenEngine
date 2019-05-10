package com.avernakis.message.bus;

import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

class AsyncMessageBusTest {
  private AsyncMessageBus messageBus = null;
  @BeforeAll
  static void setup() {
  }

  @BeforeEach
  void init() {
    messageBus = new AsyncMessageBus();
    messageBus.start();
  }

  @Test
  @DisplayName("New message type can be registered.")
  void newTypeCanBeRegistered() {
    class TestMessage implements Message {
      Boolean handlerCalled;
      void updateHandlerCalled() {
        handlerCalled = true;
      }
      @Override
      public String description() {
        return "TestMessage";
      }
    }

    Handler<TestMessage> handler = new Handler<>() {
      @Override
      Message callback(TestMessage message) {
        message.updateHandlerCalled();
        assertEquals(message.description(), "TestMessage");
        return null;
      }
    };

    messageBus.registerHandler(TestMessage.class, handler);
    TestMessage message = new TestMessage();
    messageBus.submitMessage(message);
    try {
      Thread.sleep(4);
    } catch (InterruptedException e) {
      fail();
    }
    assertTrue(message.handlerCalled);
  }

  @Test
  @DisplayName("Attempting to register the same type twice results in error.")
  void duplicateTypesCannotBeRegistered() {

  }

  @Test
  @DisplayName("Pushing a message of registered type onto the bus.")
  void messagesCanBePushed() {

  }

  @Test
  @DisplayName("Pulling a message of registered type from bus.")
  void messagesCanBePulled() {

  }

  @Test
  @DisplayName("Subscribing for events of a registered type.")
  void canSubscribeForMessages() {

  }

  @Test
  @DisplayName("Subscribing for events of a type not yet registered results in error.")
  void cannotSubscribeForUnregisteredTypes() {

  }
  @Test
  @DisplayName("Message bus executes callback when event is handled.")
  void callbacksAreExecuted() {

  }

  @Test
  @DisplayName("Result can be pushed onto queue after event is handled.")
  void resultsCanBeGenerated() {

  }

  @Test
  @DisplayName("Events can be handled and then the result ignored.")
  void eventsCanBeHandledThenIgnored() {

  }

  @AfterAll
  static void teardown() {}

  @AfterEach
  void destroy() {
    messageBus.stop();
  }

}
