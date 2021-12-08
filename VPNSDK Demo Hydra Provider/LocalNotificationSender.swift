//
//  LocalNotificationSender.swift
//  VPNSDK Demo Hydra Provider
//
//  Created by Dan Vasilev on 31.01.2021.
//

import UserNotifications

class LocalNotificationSender {
    static func sendNotification(with content: UNMutableNotificationContent, identifier: String) {
        let notificationCenter = UNUserNotificationCenter.current()

        notificationCenter.getNotificationSettings {  (settings) in
            guard settings.authorizationStatus == .authorized else {
                return
            }

            notificationCenter.removePendingNotificationRequests(withIdentifiers: [identifier])
            let request = makeRequest(content: content, identifier: identifier)

            notificationCenter.add(request, withCompletionHandler: { (error) in
                if let e = error {
                    print("Error while sending notifications. Error was: \(e.localizedDescription)")
                }
            })
        }
    }

    private static func makeRequest(content: UNMutableNotificationContent, identifier: String) -> UNNotificationRequest {
        let alertTime = Date().addingTimeInterval(2)
        var calendar = Calendar(identifier: .gregorian)
        calendar.timeZone = TimeZone.current

        let components: Set<Calendar.Component> = [.year , .month, .day, .hour, .minute, .second, .timeZone]
        let dateComponents = calendar.dateComponents(components, from: alertTime)
        let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: false)

        return UNNotificationRequest(identifier: identifier, content: content, trigger: trigger)
    }
}
