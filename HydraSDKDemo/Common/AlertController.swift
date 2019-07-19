import UIKit

class AlertController {
    typealias ActionHandler = () -> ()
    
    class func presentAlert(withTitle title: String,
                            body: String,
                            in controller: UIViewController,
                            actionButtonTitle: String? = nil,
                            cancelButtonTitle: String? = nil,
                            actionHandler: ActionHandler? = nil,
                            cancelActionHandler: ActionHandler? = nil) {
        let alertController = UIAlertController(title: title,
                                                message: body,
                                                preferredStyle: .alert)
        
        var actions: [UIAlertAction] = []
        
        if let actionTitle = actionButtonTitle, let actionHandler = actionHandler {
            let action = UIAlertAction(title: actionTitle, style: .default, handler: { _ in
                actionHandler()
            })
            actions.append(action)
        }
        
        if let cancelTitle = cancelButtonTitle, let cancelHandler = cancelActionHandler {
            let cancelAction = UIAlertAction(title: cancelTitle, style: .cancel) { _ in
                cancelHandler()
        }
            actions.append(cancelAction)
        }
        
        actions.forEach { alertController.addAction($0) }
        
        controller.present(alertController, animated: true, completion: nil)
    }
}
