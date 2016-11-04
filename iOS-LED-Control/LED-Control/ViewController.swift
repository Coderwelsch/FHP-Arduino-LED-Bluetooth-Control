//
//  ViewController.swift
//  LED-Control
//
//  Created by Joseph Ribbe on 26/10/2016.
//  Copyright © 2016 Coderwelsch. All rights reserved.
//

import UIKit
import CoreBluetooth

class ViewController: UIViewController,CBCentralManagerDelegate, CBPeripheralDelegate {
    
    var manager:CBCentralManager!
    var peripheral:CBPeripheral!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        manager = CBCentralManager(delegate: self, queue: nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state == CBManagerState.poweredOn {
            NSLog("Start searching")
            central.scanForPeripherals(withServices: nil, options: nil)
        } else {
            print("Bluetooth not available.")
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        if let name = peripheral.name {
            NSLog("%s", name);
        } else {
            NSLog("Device found, but no name set, RSSI: %s")
        }
    }
}

