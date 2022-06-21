import React from "react";
import ThemedText from "../ThemedText";
import ThemedTouchableOpacity from "../ThemedTouchableOpacity";
import ThemedView from "../ThemedView";
import * as LocalAuthentication from "expo-local-authentication";

import { styles } from "./styles";

interface AuthButtonProps {
  onAuthenticated: () => void;
}

export default function AuthButton(props: AuthButtonProps) {
  const tryToAuth = async () => {
    const auth = await LocalAuthentication.authenticateAsync({
      promptMessage:
        "Autenticação obrigatória para acessar a telemetria do robô",
      cancelLabel: "Cancelar",
      requireConfirmation: false,
    });

    if (auth.success) {
      props.onAuthenticated();
    } else {
      return;
    }
  };

  return (
    <ThemedView darkColor="#1c1c1c" style={styles.container}>
      <ThemedText style={styles.text}>
        Aperte o botão para se autenticar e
      </ThemedText>
      <ThemedText style={styles.text}>
        ter acesso a telemetria do robô
      </ThemedText>
      <ThemedTouchableOpacity style={styles.button} onPress={tryToAuth}>
        <ThemedText style={styles.buttonText}>Autenticar</ThemedText>
      </ThemedTouchableOpacity>
    </ThemedView>
  );
}
