import cv2
import urllib.request
import numpy as np
import time
from pydrive.drive import GoogleDrive
from pydrive.auth import GoogleAuth

# 🔹 Authenticate with Google Drive
gauth = GoogleAuth()
gauth.LocalWebserverAuth()
drive = GoogleDrive(gauth)

# 🔹 Google Drive folder ID (Extract only the ID from your folder URL)
folder_id = "1aPYmslSeWhzSJY7HTXsxu6IdT-W5LvUA"

# 🔹 Correct URL to capture an image
url = "http://192.168.137.115/capture"  # Change if needed

cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)

count = 0

while True:
    try:
        print("📷 Fetching image from ESP32-CAM...")
        img_resp = urllib.request.urlopen(url)
        imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgnp, -1)

        # 🔹 Check if the image is empty
        if frame is None or frame.size == 0:
            print("❌ Error: Received an empty image from ESP32-CAM")
            continue  # Skip this loop iteration

        print("✅ Image received successfully!")
        cv2.imshow("live transmission", frame)

        # 🔹 Capture an image every 10 seconds
        count += 1
        t = f"{count}.png"
        cv2.imwrite(t, frame)
        print(f"✅ Image saved: {t}")

        # 🔹 Upload to Google Drive
        print("📤 Uploading image to Google Drive...")
        f = drive.CreateFile({'parents': [{'id': folder_id}], 'title': t})
        f.SetContentFile(t)
        f.Upload()
        print(f"✅ Image uploaded: {t}")

        # 🔹 Wait for 5 minutes before capturing again
        time.sleep(300)

    except Exception as e:
        print(f"❌ Error: {e}")
        time.sleep(5)

cv2.destroyAllWindows()
