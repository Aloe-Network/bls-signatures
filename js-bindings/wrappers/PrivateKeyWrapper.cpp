// Copyright 2021 Aloe, LLC

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "PrivateKeyWrapper.h"

namespace js_wrappers {
PrivateKeyWrapper::PrivateKeyWrapper(const PrivateKey &privateKey) : JSWrapper(privateKey) {}

const size_t PrivateKeyWrapper::PRIVATE_KEY_SIZE = PrivateKey::PRIVATE_KEY_SIZE;

std::vector <PrivateKey> PrivateKeyWrapper::Unwrap(std::vector <PrivateKeyWrapper> wrappers) {
    std::vector <PrivateKey> unwrapped;
    for (auto &wrapper : wrappers) {
        unwrapped.push_back(wrapper.GetWrappedInstance());
    }
    return unwrapped;
}

PrivateKeyWrapper PrivateKeyWrapper::Aggregate(val privateKeysArray) {
    std::vector <PrivateKey> privateKeys = PrivateKeyWrapper::Unwrap(
            helpers::toVectorFromJSArray<PrivateKeyWrapper>(privateKeysArray));

    PrivateKey aggregatedSk = PrivateKey::Aggregate(privateKeys);
    return PrivateKeyWrapper(aggregatedSk);
}

PrivateKeyWrapper PrivateKeyWrapper::FromBytes(val buffer, bool modOrder) {
    std::vector <uint8_t> bytes = helpers::toVector(buffer);
    const bls::Bytes bytesView(bytes);
    PrivateKey pk = PrivateKey::FromBytes(bytesView, modOrder);
    return PrivateKeyWrapper(pk);
}

val PrivateKeyWrapper::Serialize() const {
    return helpers::toUint8Array(wrapped.Serialize());
}

PrivateKeyWrapper PrivateKeyWrapper::Deepcopy() {
    return PrivateKeyWrapper(GetWrappedInstance());
}

G1ElementWrapper PrivateKeyWrapper::GetG1() const {
    G1Element pk = wrapped.GetG1Element();
    return G1ElementWrapper(pk);
}
}  // namespace js_wrappers
appers
