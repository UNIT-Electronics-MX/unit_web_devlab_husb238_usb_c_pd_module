# 🚀 Configuración de GitHub Pages

Este documento explica cómo configurar GitHub Pages para desplegar automáticamente las aplicaciones web.

## ✅ Configuración Inicial (Solo una vez)

### Paso 1: Habilitar GitHub Pages

1. Ve a tu repositorio en GitHub
2. Click en **Settings** (Configuración)
3. En el menú lateral, click en **Pages**
4. En **Source**, selecciona:
   - **Source**: `GitHub Actions`

![GitHub Pages Settings](https://docs.github.com/assets/cb-47267/mw-1440/images/help/pages/publishing-source-drop-down.webp)

### Paso 2: Verificar el Workflow

1. Ve a la pestaña **Actions**
2. Deberías ver el workflow **"Deploy to GitHub Pages"**
3. Si hay algún error, revisa los logs

## 🔄 Despliegue Automático

Cada vez que hagas un push a la rama `main` con cambios en la carpeta `docs/`, el workflow automáticamente:

1. ✅ Detecta los cambios
2. 📦 Empaqueta la carpeta `docs/`
3. 🚀 Despliega a GitHub Pages
4. ✨ La aplicación estará disponible en 1-2 minutos

### URL de tu aplicación:

```
https://<usuario>.github.io/<repositorio>/index-husb238.html
```

**Para este proyecto:**
```
https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html
```

## 🛠️ Despliegue Manual

Si necesitas forzar un despliegue sin hacer cambios:

1. Ve a **Actions**
2. Selecciona **"Deploy to GitHub Pages"**
3. Click en **Run workflow**
4. Selecciona la rama `main`
5. Click en **Run workflow**

## 📁 Archivos del Workflow

```
.github/
└── workflows/
    └── deploy-gh-pages.yml    # Configuración del workflow
```

### Qué hace el workflow:

```yaml
# Se ejecuta cuando:
- Hay un push a main con cambios en docs/
- Se ejecuta manualmente (workflow_dispatch)

# Pasos:
1. Checkout del código
2. Configurar GitHub Pages
3. Subir la carpeta docs/ como artifact
4. Desplegar a GitHub Pages
```

## 🔍 Verificar el Despliegue

### Ver el estado:

1. Ve a **Actions**
2. Click en el workflow más reciente
3. Verifica que todos los pasos estén en verde ✅

### Tiempo de despliegue:

- ⏱️ Generalmente toma **1-2 minutos**
- 🔄 Puede tardar hasta **5 minutos** en propagarse

### Ver los logs:

1. **Actions** → Click en el workflow
2. Click en **deploy**
3. Expande cada paso para ver detalles

## 🐛 Solución de Problemas

### Error: "Publishing source not configured"

**Solución:**
1. Settings → Pages
2. Source: Selecciona `GitHub Actions`

### Error: "Permission denied"

**Solución:**
1. Settings → Actions → General
2. Scroll hasta "Workflow permissions"
3. Selecciona: `Read and write permissions`
4. ✅ Activa: `Allow GitHub Actions to create and approve pull requests`

### Error: "404 - Page not found"

**Causas comunes:**
1. El despliegue aún está en proceso (espera 2-5 min)
2. La URL está mal escrita
3. GitHub Pages no está habilitado

**Verificar:**
```bash
# URL correcta
https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html

# URLs disponibles
/index-husb238.html    # Aplicación principal
/test-ble.html         # Página de prueba
/diagrama.html         # Diagrama del sistema
/index.html            # Pulsar H2 reference
```

### La página no se actualiza

**Solución:**
1. Limpia la caché del navegador (Ctrl + Shift + R)
2. Espera 2-5 minutos para propagación
3. Verifica que el workflow se haya ejecutado correctamente

## 📊 Monitoreo

### Ver estadísticas de uso:

1. Settings → Pages
2. Scroll hasta **"Insights"**
3. Ver visitantes y páginas más vistas

### Ver builds históricos:

1. Actions → "Deploy to GitHub Pages"
2. Ver todos los despliegues pasados

## 🎯 Mejores Prácticas

### ✅ Hacer
- Probar cambios localmente antes de hacer push
- Revisar los logs del workflow si algo falla
- Usar commits descriptivos

### ❌ Evitar
- Hacer push sin probar
- Ignorar errores en el workflow
- Subir archivos muy grandes (> 1MB)

## 🔐 Seguridad

GitHub Pages sirve archivos estáticos con HTTPS automáticamente:
- ✅ `https://` - Seguro (Web Bluetooth funciona)
- ❌ `http://` - No seguro (Web Bluetooth bloqueado)

## 📝 Notas Adicionales

### Archivos importantes:

```
docs/
├── .nojekyll          # Desactiva Jekyll (importante!)
├── README.md          # Documentación de la carpeta
├── index-husb238.html # Página principal
└── ...                # Otros archivos
```

### ¿Por qué `.nojekyll`?

GitHub Pages usa Jekyll por defecto, lo que puede causar problemas con archivos que empiezan con `_` o tienen ciertas estructuras. El archivo `.nojekyll` desactiva esto.

### Dominios personalizados

Si quieres usar un dominio personalizado:

1. Settings → Pages → Custom domain
2. Ingresa tu dominio (ej: `husb238.tudominio.com`)
3. Configura DNS según las instrucciones

## 🆘 Soporte

Si tienes problemas:

1. 📖 Revisa la [documentación oficial de GitHub Pages](https://docs.github.com/pages)
2. 🔍 Busca en [GitHub Community](https://github.community/)
3. 📧 Contacta al equipo de UNIT Electronics

---

**Última actualización**: Febrero 2026  
**Mantenido por**: UNIT Electronics
