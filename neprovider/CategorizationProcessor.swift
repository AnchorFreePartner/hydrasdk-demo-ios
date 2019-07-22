import Foundation
import VPNTunnelProviderSDK.AFHydraCategorization
import UserNotifications

class CategorizationProcessor {
    let notificationRequestIdentifier = "com.anchorfree.HydraTestApp.neprovider.CategorizatioProcessor.notificationRequestIdentifier"
    
    func process(_ hydraCategorization: AFHydraCategorization) {
        sendUserNotificationIfAuthorized(hydraCategorization)
    }
    
    private func sendUserNotificationIfAuthorized(_ hydraCategorization: AFHydraCategorization) {
        let notificationCenter = UNUserNotificationCenter.current()
        notificationCenter.getNotificationSettings { [unowned self] (settings) in
            guard settings.authorizationStatus == .authorized else {return}
            
                notificationCenter.removePendingNotificationRequests(withIdentifiers: [self.notificationRequestIdentifier])
                let content = hydraCategorization.userNotificationContent
                let alertTime = Date().addingTimeInterval(2)
                var calendar = Calendar(identifier: .gregorian)
                calendar.timeZone = TimeZone.current
                let components: Set<Calendar.Component> = [.year , .month, .day, .hour, .minute, .second, .timeZone]
                let dateComponents = calendar.dateComponents(components, from: alertTime)
                let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: false)
                let request = UNNotificationRequest(identifier: self.notificationRequestIdentifier, content: content, trigger: trigger)
                notificationCenter.add(request, withCompletionHandler: { (error) in
                    if let e = error {
                        print("Error while sending notifications. Error was: \(e.localizedDescription)")
                    }
                })
            }
    }
}

fileprivate extension AFHydraCategorization {
    var userNotificationContent: UNMutableNotificationContent {
        let content = UNMutableNotificationContent()
        
        var sourcesText = ""
        for source in self.sources {
            if !sourcesText.isEmpty {
                sourcesText.append(",")
            }
            sourcesText.append(" \(source)")
        }
        var categoryText = ""
        if let category_label = self.category_label {
            categoryText = " CAT: \(category_label);"
        }
        var timestampText = ""
        if let timestamp = self.timestamp {
            timestampText = " T: \(timestamp)"
        }
        
        content.title = self.resource
        content.body = "\(self.actionEmoji)\(categoryText) SRC: \(sourcesText);\(timestampText)"
        return content
    }
}
