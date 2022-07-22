#ifndef __Exception_h__
#define __Exception_h__

class GameMoveError {
    std::string message;

   public:
    GameMoveError(std::string message);

    // Returns the message associated with the exception.
    const std::string &what() const;
};

#endif
