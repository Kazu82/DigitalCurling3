﻿// MIT License
// 
// Copyright (c) 2022 UEC Takeshi Ito Laboratory
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DIGITALCURLING3_SRC_SIMULATORS_FCV1_SIMULATOR_HPP
#define DIGITALCURLING3_SRC_SIMULATORS_FCV1_SIMULATOR_HPP

#include "digitalcurling3/detail/i_simulator.hpp"
#include "digitalcurling3/detail/simulators/fcv1_simulator_factory.hpp"
#include "simulators_fcv1_simulator_storage.hpp"
#include "box2d_util.hpp"

namespace digitalcurling3::simulators {

class FCV1SimulatorStorage;

/// <summary>
/// Friction-CurlVelocity式シミュレータ1
/// </summary>
class FCV1Simulator : public ISimulator {
public:

    static constexpr float kStoneMass = 19.96f;  // ストーンの質量[kg]

    explicit FCV1Simulator(FCV1SimulatorFactory const& factory);
    explicit FCV1Simulator(FCV1SimulatorStorage const& storage);

    virtual void SetStones(AllStones const& stones) override;
    virtual void Step() override;

    virtual AllStones const& GetStones() const override;
    virtual std::vector<Collision> const& GetCollisions() const override;
    virtual bool AreAllStonesStopped() const override;
    virtual float GetSecondsPerFrame() const override;

    virtual std::string GetSimulatorId() const override
    {
        return std::string(kFCV1SimulatorId);
    }

    virtual ISimulatorFactory const& GetFactory() const override;

    virtual std::unique_ptr<ISimulatorStorage> CreateStorage() const override;
    virtual void Save(ISimulatorStorage & storage) const override;
    virtual void Load(ISimulatorStorage const& storage) override;

    virtual ~FCV1Simulator() = default;

    class ContactListener : public b2ContactListener {
    public:
        ContactListener(FCV1Simulator * instance) : instance_(instance) {}
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    private:
        FCV1Simulator * const instance_;
    };

private:
    mutable FCV1SimulatorStorage storage_;
    b2World world_;
    std::array<b2Body*, kStoneMax> stone_bodies_;
    mutable bool stones_dirty_;
    mutable bool all_stones_stopped_;
    mutable bool all_stones_stopped_dirty_;
    ContactListener contact_listener_;

    // ストレージのデータを内部データに適用する
    void UpdateWithStorage();
};

} // namespace digitalcurling3::simulation

#endif // DIGITALCURLING3_SRC_SIMULATORS_FCV1_SIMULATOR_HPP
