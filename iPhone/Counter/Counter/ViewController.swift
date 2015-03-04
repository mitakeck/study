//
//  ViewController.swift
//  Counter
//
//  Created by mitake on 2015/03/01.
//  Copyright (c) 2015年 三井 健史. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var counter: UILabel!
    var countNum = 0;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    
    func setCounterLabel(countNum : Int){
        counter.text = String(countNum);
    }

    @IBAction func PushCounterButton(sender: AnyObject) {
        countNum++;
        setCounterLabel(countNum);
    }
    @IBAction func PushResetCounterButton(sender: AnyObject) {
        countNum = 0;
        setCounterLabel(countNum);
    }

}

