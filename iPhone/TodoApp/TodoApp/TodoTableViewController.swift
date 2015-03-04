//
//  TodoTableViewController.swift
//  TodoApp
//
//  Created by mitake on 3/4/15.
//  Copyright (c) 2015 三井 健史. All rights reserved.
//

import Foundation
import UIkit

class TodoTableViewController : UIViewController{
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let title = UILabel(frame: CGRect(x: 10, y: 20, width: 310, height: 44))
        title.text = "Hello Swift"
        self.view.addSubview(title)
    }
}
