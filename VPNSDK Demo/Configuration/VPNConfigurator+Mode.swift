//
//  VPNConfigurator+Mode.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 31.01.2021.
//

import Foundation
import VPNApplicationSDK

extension VPNConfigurator {
    enum Mode: Equatable {
        case single(VPNProtocolType)
        case composed(ComposedMode)
    }

    enum ComposedMode: Equatable {
        case manual(selectedProtocol: VPNProtocolType)
        case auto(protocolPriority: [VPNProtocolType])
    }
}

extension VPNConfigurator.Mode: Codable {
    private enum Base: Int, Codable {
        case single
        case composed
    }

    private enum CodingKeys: String, CodingKey {
        case base
        case singleProtocol
        case composedMode
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        let base = try container.decode(Base.self, forKey: .base)

        switch base {
        case .single:
            let currentProtocol = try container.decode(VPNProtocolType.self, forKey: .singleProtocol)
            self = .single(currentProtocol)
        case .composed:
            let composedMode = try container.decode(VPNConfigurator.ComposedMode.self, forKey: .composedMode)
            self = .composed(composedMode)
        }
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)

        switch self {
        case .single(let currentProtocol):
            try container.encode(Base.single, forKey: .base)
            try container.encode(currentProtocol, forKey: .singleProtocol)
        case .composed(let composedMode):
            try container.encode(Base.composed, forKey: .base)
            try container.encode(composedMode, forKey: .composedMode)
        }
    }
}

extension VPNConfigurator.ComposedMode: Codable {
    private enum Base: Int, Codable {
        case manual
        case auto
    }

    private enum CodingKeys: String, CodingKey {
        case base
        case manualSelectedProtocol
        case autoProtocolPriority
    }

    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        let base = try container.decode(Base.self, forKey: .base)

        switch base {
        case .manual:
            let selectedProtocol = try container.decode(VPNProtocolType.self, forKey: .manualSelectedProtocol)
            self = .manual(selectedProtocol: selectedProtocol)
        case .auto:
            let protocolPriority = try container.decode([VPNProtocolType].self, forKey: .autoProtocolPriority)
            self = .auto(protocolPriority: protocolPriority)
        }
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)

        switch self {
        case .manual(let selectedProtocol):
            try container.encode(Base.manual, forKey: .base)
            try container.encode(selectedProtocol, forKey: .manualSelectedProtocol)
        case .auto(let protocolPriority):
            try container.encode(Base.auto, forKey: .base)
            try container.encode(protocolPriority, forKey: .autoProtocolPriority)
        }
    }
}

extension VPNProtocolType: Codable { }
