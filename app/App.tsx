import { StatusBar } from "expo-status-bar";
import { useState } from "react";
import {
  Alert,
  PermissionsAndroid,
  StyleSheet,
  useColorScheme,
} from "react-native";
import { BleManager } from "react-native-ble-plx";
import ThemedView from "./components/ThemedView";
import AuthScreen from "./screens/AuthScreen";
import ConnectBLEscreen from "./screens/ConnectBLEscreen";
import NotFoundScreen from "./screens/NotFoundScreen";

export default function App() {
  // Screens
  // 0: Auth
  // 1: Conectar ao Bluetooth

  const [screen, setScreen] = useState(1);

  let bluetoothManager = new BleManager();
  const startNewManager = () => {
    bluetoothManager.destroy();
    bluetoothManager = new BleManager();
  };

  startNewManager();
  (async () => {
    if (
      await PermissionsAndroid.check("android.permission.ACCESS_FINE_LOCATION")
    ) {
    } else {
      const granted = await PermissionsAndroid.request(
        "android.permission.ACCESS_FINE_LOCATION"
      );
      if (granted === "granted") {
      }
    }
  })();

  return (
    <>
      {screen === 0 && (
        <AuthScreen
          onAuthenticated={() => {
            setScreen(1);
          }}
        />
      )}
      {screen === 1 && (
        <ConnectBLEscreen
          bluetoothManager={bluetoothManager}
          startNewManager={startNewManager}
        />
      )}
      {screen > 1 || screen < 0 ? (
        <NotFoundScreen setScreen={() => setScreen(0)} />
      ) : null}
    </>
  );
  // <ThemedView style={styles.container} lightColor="#eee" darkColor="#1f1f1f">
  //   {/* <ThemedText lightColor="#1c1c2c" darkColor="#eee">
  //     Conecte a um dispositivo
  //   </ThemedText>
  //   <StatusBar style="auto" />
  //   <ThemedText lightColor="#1c1c2c" darkColor="#eee">
  //     {isBiometricSupported ? "Suporta" : "Nope"}
  //   </ThemedText> */}
  // </ThemedView>
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: "center",
    justifyContent: "center",
  },
});
