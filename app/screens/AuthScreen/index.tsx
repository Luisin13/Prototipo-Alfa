import React, { useEffect, useState } from "react";
import * as LocalAuthentication from "expo-local-authentication";
import AuthButton from "../../components/AuthButton";
import ThemedText from "../../components/ThemedText";
import ThemedView from "../../components/ThemedView";

import { styles } from "./styles";

interface AuthScreenProps {
  onAuthenticated: () => void;
}

export default function AuthScreen(props: AuthScreenProps) {
  const [isBiometricSupported, setIsBiometricSupported] = useState(false);

  useEffect(() => {
    (async () => {
      const compatible = await LocalAuthentication.hasHardwareAsync();
      setIsBiometricSupported(compatible);
    })();
  });
  
  return (
    <ThemedView style={styles.container} lightColor="#eee" darkColor="#1f1f1f">
      {isBiometricSupported ? (
        <AuthButton
          onAuthenticated={props.onAuthenticated}
        />
      ) : (
        <ThemedText lightColor="#1c1c2c" darkColor="#eee">
          Biometria não é suportada, não foi possível autenticar
        </ThemedText>
      )}
    </ThemedView>
  );
}
