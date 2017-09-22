//
//  CountryController.swift
//  HydraSDKDemo
//
//  Created by Igor Glotov on 9/21/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import HydraApplicationSDK

protocol CountryControllerProtocol {
    func countryChanged(newCountry: AFCountry)
}

class CountryController: UITableViewController {
    var delegate: CountryControllerProtocol?
    var currentCountry: AFCountry?
    var countryList: Array<AFCountry>?
    
    var hydraClient : AFHydra {
        get {
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            return appDelegate.hydraClient
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        hydraClient.availableCountries { [weak self] (e, countries) in
            if let ex = e {
                print("Countries error: \(ex)")
            } else {
                print("Countries success")
            }
            
            self?.countryList = countries
            self?.tableView.reloadData()
        }
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.countryList?.count ?? 0
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "DefaultCell", for: indexPath)
        guard let countryList = self.countryList else { return cell }
        let country = countryList[indexPath.row]
        var labelString: String = country.countryCode as String!
        if self.currentCountry?.countryCode == country.countryCode {
            labelString += " (selected)"
        }
        cell.textLabel?.text = labelString
        return cell
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        guard let countryList = self.countryList else { return }
        delegate?.countryChanged(newCountry: countryList[indexPath.row])
        dismiss(animated: true, completion: nil)
    }
}
