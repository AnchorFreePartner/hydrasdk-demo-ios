//
//  VPNService.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 26.01.2021.
//

import Foundation
import VPNApplicationSDK

protocol VPNService {
    var state: VPNState { get }
    func login(method: AuthMethod, completion: @escaping UserCompletion)
    func start(location: VirtualLocation?, completion: @escaping StartStateCompletion)
    func stop(completion: @escaping StateCompletion)
}

extension VPNSDK: VPNService { }

extension ComposedVPNSDK: VPNService { }
