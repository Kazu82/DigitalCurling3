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

#include "digitalcurling3/detail/i_player_factory.hpp"
#include "digitalcurling3/detail/players/player_identical_factory.hpp"
#include "digitalcurling3/detail/players/player_normal_dist_factory.hpp"
#include "digitalcurling3/detail/players/player_original1_factory.hpp"

namespace digitalcurling3::polymorphic_json::detail {

template <>
ToJsonRegistry<IPlayerFactory> & GetToJsonRegistry<IPlayerFactory>()
{
    static ToJsonRegistry<IPlayerFactory> registry{
        { typeid(players::PlayerIdenticalFactory), ToJsonFuncTemplate<IPlayerFactory, players::PlayerIdenticalFactory> },
        { typeid(players::PlayerNormalDistFactory), ToJsonFuncTemplate<IPlayerFactory, players::PlayerNormalDistFactory> },
        { typeid(players::PlayerOriginal1Factory), ToJsonFuncTemplate<IPlayerFactory, players::PlayerOriginal1Factory> },
    };
    return registry;
}

template <>
FromJsonRegistry<IPlayerFactory> & GetFromJsonRegistry<IPlayerFactory>()
{
    static FromJsonRegistry<IPlayerFactory> registry{
        { std::string(players::kPlayerIdenticalId), FromJsonFuncTemplate<IPlayerFactory, players::PlayerIdenticalFactory> },
        { std::string(players::kPlayerNormalDistId), FromJsonFuncTemplate<IPlayerFactory, players::PlayerNormalDistFactory> },
        { std::string(players::kPlayerOriginal1Id), FromJsonFuncTemplate<IPlayerFactory, players::PlayerOriginal1Factory> },
    };
    return registry;
}

} // namespace digitalcurling3::polymorphic_json::detail
