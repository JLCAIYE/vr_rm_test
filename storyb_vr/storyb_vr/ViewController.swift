//
//  ViewController.swift
//  storyb_vr
//
//  Created by CAIYUE LAI on 8/24/23.
//

import UIKit

class ViewController: UIViewController {


    @IBOutlet weak var textlabel: UITextView!
    
    @IBOutlet weak var textl: UITextView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    @IBAction func newbutton(_ sender: UIButton) {
        textl.text = "hello world"
    }
    
}

