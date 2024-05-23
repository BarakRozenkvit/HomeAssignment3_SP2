class Card{};

class Resource{
    int _counter;

    public:
        Resource(){
            _counter = 0;
        }

};
class Wood: public Resource{};
class Brick: public Resource{};
class Wool: public Resource{};
class Iron: public Resource{};
class Wheat: public Resource{};

class Development: public Card{};
class Promotion: public Development{};
class Knights: public Development{};
class WinPoints: public Development{};

class Monopol: public Promotion{
    Resource desired_resource;
};
class Builder: public Promotion{};
class WealthyYear: public Promotion{};