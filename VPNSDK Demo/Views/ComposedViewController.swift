//
//  ComposedViewController.swift
//  VPNSDK Demo
//
//  Created by Dan Vasilev on 27.01.2021.
//

import UIKit

class ComposedViewController: SDKViewController {
    // MARK: - Overrides

    override func prepareMode() {
        switch configurator.currentMode {
        case .single:
            configurator.currentMode = .composed(.manual(selectedProtocol: .hydra))
        case .composed:
            break
        }
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        didSelectType(at: indexPath)
    }

    // MARK: - Private

    private func didSelectType(at indexPath: IndexPath) {
        guard
            let cell = tableView.cellForRow(at: indexPath) as? ComposedTypeCell,
            let mode = cell.mode
        else {
            return
        }
        configurator.currentMode = .composed(mode)
    }
}
