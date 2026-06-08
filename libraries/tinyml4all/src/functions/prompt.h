#pragma once

namespace tinyml4all {
    /**
     * Prompt user for String value
     * @param msg
     * @return
     */
    String promptString(String msg) {
        Serial.print(msg);
        Serial.print(' ');

        size_t timeout = millis() + 8000;

        while (millis() < timeout && !Serial.available())
            delay(50);

        // display prompt again after timeout
        if (!Serial.available()) {
            Serial.println();
            return promptString(msg);
        }

        String answer = Serial.readStringUntil('\n');
        answer.trim();
        Serial.println(answer);

        // flush Serial
        while (Serial.available())
            Serial.read();

        return answer;
    }

    /**
     * Prompt user for integer value
     * @param msg
     * @return
     */
    long promptInt(String msg) {
        return promptString(msg).toInt();
    }

    /**
     * Prompt user for float value
     * @param msg
     * @return
     */
    float promptFloat(String msg) {
        return promptString(msg).toFloat();
    }
}