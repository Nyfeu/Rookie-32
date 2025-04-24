#ifndef I_MOBILITY_STRATEGY_HPP
#define I_MOBILITY_STRATEGY_HPP

class IMobilityStrategy {
    public:
        virtual void move(float x, float y) = 0;
        virtual ~IMobilityStrategy() {}
};

#endif /* I_MOBILITY_STRATEGY_HPP */