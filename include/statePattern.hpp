
enum class DoorStates { Opening, Closing, Stopped };

class GarageRemoteContext;

class State {
   public:
    virtual ~State() = default;
    virtual DoorStates handle(GarageRemoteContext&) = 0;
    virtual DoorStates getDoorState() = 0;
};

class OpenState : public State {
   public:
    DoorStates getDoorState() { return DoorStates::Opening; }
    DoorStates handle(GarageRemoteContext&) override;
};

class CloseState : public State {
   public:
    DoorStates getDoorState() { return DoorStates::Closing; }
    DoorStates handle(GarageRemoteContext&) override;
};

class StoppedState : public State {
   public:
    DoorStates getDoorState() { return DoorStates::Stopped; }
    DoorStates handle(GarageRemoteContext&) override;
};

class DummyButton {
    bool _isClicked = false;

   public:
    void click() { _isClicked = true; }

    bool isClicked() {
        int retVal = _isClicked;
        _isClicked = false;
        return retVal;
    }
};

class DummyDoor {
    bool _isClosing = true;

   public:
    void open() { _isClosing = false; }
    void close() { _isClosing = true; }
    bool isClosing() { return _isClosing; };
};

class GarageRemoteContext {
    State* _state;

   public:
    GarageRemoteContext(DummyDoor& doorRef, DummyButton& button)
        : _state(new StoppedState), door(doorRef), remoteButton(button) {}
    ~GarageRemoteContext() { delete _state; }

    DummyDoor& door;
    DummyButton& remoteButton;

    DoorStates handle();
    void changeState(State* state);
    State& getState() { return *_state; }
};
