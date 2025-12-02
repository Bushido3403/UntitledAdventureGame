param(
    [Parameter(Mandatory=$true)]
    [string]$ExePath
)

if (-not (Test-Path $ExePath)) {
    Write-Error "Executable not found: $ExePath"
    exit 1
}

# Find the certificate
$cert = Get-ChildItem -Path Cert:\CurrentUser\My | Where-Object { $_.Subject -eq "CN=Kyle Buchanan" }

if (-not $cert) {
    Write-Error "Certificate not found. Run create-certificate.ps1 first."
    exit 1
}

# Sign the executable
$signtool = "C:\Program Files (x86)\Windows Kits\10\bin\10.0.22621.0\x64\signtool.exe"

if (-not (Test-Path $signtool)) {
    # Try to find signtool in common locations
    $signtool = Get-ChildItem "C:\Program Files (x86)\Windows Kits\" -Recurse -Filter "signtool.exe" | 
                Select-Object -First 1 -ExpandProperty FullName
}

if (-not $signtool) {
    Write-Error "signtool.exe not found. Install Windows SDK."
    exit 1
}

& $signtool sign /a /n "Kyle Buchanan" /t http://timestamp.digicert.com /fd SHA256 $ExePath

if ($LASTEXITCODE -eq 0) {
    Write-Host "Successfully signed: $ExePath"
} else {
    Write-Error "Failed to sign executable"
    exit 1
}