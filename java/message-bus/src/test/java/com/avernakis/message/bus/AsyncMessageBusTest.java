package com.avernakis.message.bus;

import org.junit.jupiter.api.*;

class AsyncMessageBusTest {
  @BeforeAll
  static void setup() {

  }

  @BeforeEach
  void init() {

  }

  @Test
  @DisplayName("Empty queue is handled with timeout.")
  void emptyQueueProducesTimeout() {

  }

  @Test
  @DisplayName("Empty queue is handled with blocking.")
  void emptyQueueBlocks() {

  }

  @Test
  @DisplayName("New message type can be registered.")
  void newTypeCanBeRegistered() {

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
  void destroy() {}

}
